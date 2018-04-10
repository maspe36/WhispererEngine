//
// Created by Sam on 9/25/2017.
//

#include <random>
#include <utility>

#include "../../include/Game/Game.h"
#include "../../include/Game/Card.h"
#include "../../include/Game/Player.h"
#include "../../include/Game/Effect.h"
#include "../../include/Network/Client.h"
#include "../../include/Network/Server.h"
#include "../../include/Game/Event/Game/StartGameEvent.h"
#include "../../include/Game/Event/Game/EndGameEvent.h"

json Game::getJSON(const std::shared_ptr<Player>& toPlayer)
{
    json gameJSON;

    gameJSON["players"] = getPlayersJSON(toPlayer);

    return gameJSON;
}

std::vector<json> Game::getPlayersJSON(std::shared_ptr<Player> toPlayer)
{
    std::vector<json> playersJSON;

    for (const auto& player : players)
    {
        json playerJSON;

        if (player->tag == toPlayer->tag)
        {
            playerJSON = player->getState();
        }
        else
        {
            playerJSON = player->getOpponentState();
        }

        playersJSON.push_back(playerJSON);
    }

    return playersJSON;
}

std::vector<json> Game::getOpponentJSON(std::shared_ptr<Player> toPlayer)
{
    std::vector<json> opponentsJSON;
    std::vector<std::shared_ptr<Player>> opponents = getOpponents(std::move(toPlayer));

    for (const auto& player : opponents)
    {
        auto opponentJSON = player->getOpponentState();
        opponentsJSON.push_back(opponentJSON);
    }

    return opponentsJSON;
}

bool Game::isGameOver()
{
    std::vector<std::shared_ptr<Player>> alive;

    for (const auto& player : players)
    {
        if (player->health > 0)
        {
            alive.push_back(player);
        }
    }

    // Will return true when more players exist in the game than players that are alive
    return players.size() > alive.size();
}

std::shared_ptr<Player> Game::getWinner()
{
    std::vector<std::shared_ptr<Player>> alive;

    // Is a players health zero?
    for (const auto& player : players)
    {
        if (player->health > 0)
        {
            alive.push_back(player);
        }
    }

    // Did a player leave?
    if (players.size() == 1)
    {
        alive.push_back(players.front());
    }

    // Will need to change this if we ever want say 2v2
    return alive.at(0);
}

void Game::surrender(std::shared_ptr<Player> player)
{
    // Surrender a player is still connected so send them back to the lobby before they quit the game
    player->client->resetLobbyListen();
    quit(player);
}

void Game::quit(std::shared_ptr<Player> player)
{
    removePlayer(player);
    endGame();
}

std::shared_ptr<Player> Game::findPlayer(const std::string &tag)
{
    for (const auto& player : players)
    {
        if (player->tag == tag)
        {
            return player;
        }
    }

    throw std::runtime_error("No player with this tag (" + tag + ") was found");
}

std::vector<std::shared_ptr<Player>> Game::getOpponents(std::shared_ptr<Player> forPlayer)
{
    std::vector<std::shared_ptr<Player>> opponents;

    for (const auto& player : players)
    {
        if (forPlayer != player)
        {
            opponents.push_back(player);
        }
    }

    return opponents;
}

void Game::removePlayer(std::shared_ptr<Player> player)
{
    players.erase(std::remove(players.begin(), players.end(), player));
}

void Game::writePlayers(const std::string &data)
{
    for (const auto& player : players)
    {
        player->client->write(data);
    }
}

void Game::registerPlayers()
{
    for (const auto& player : players)
    {
        player->game = shared_from_this();
    }
}

void Game::startGame()
{
    for (const auto& player : players)
    {
        player->startGameSetup();
    }

    std::shuffle(players.begin(), players.end(), std::mt19937(std::random_device()()));
    activePlayer = players.front();

    // Check for game start effects
    StartGameEvent startGameEvent(shared_from_this());
    eventHandler(std::make_shared<StartGameEvent>(startGameEvent));
}

void Game::changeTurn()
{
    for (const auto& player : players)
    {
        if (player->tag != activePlayer->tag)
        {
            activePlayer = player;
            break;
        }
    }

    activePlayer->startTurn();
}

void Game::endGame()
{
    auto winner = getWinner();

    EndGameEvent endGameEvent(shared_from_this(), winner);
    eventHandler(std::make_shared<EndGameEvent>(endGameEvent));

    server->endGame(shared_from_this());
}

void Game::eventHandler(const std::shared_ptr<Event>& event)
{
    // Make a copy of history to compare with after all events and
    // effects from this starting event are resolved and recorded
    std::vector<std::shared_ptr<Event>> oldHistory = history;

    history.push_back(event);
    queueEffects(event);
    solveEffects();

    // Send the messages to clients for all new events
    std::vector<std::shared_ptr<Event>> historyDiff = getHistoryDifference(oldHistory);

    for (const auto& env : historyDiff)
    {
        env->sendMessage();
    }
}

Game::Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server)
        : players(std::move(players)), server(std::move(server))
{
    for (auto const& player : players)
    {
        player->refreshDeck();
    }
}

Game::~Game()
= default;

void Game::queueEffects(const std::shared_ptr<Event>& event)
{
    for (const auto& card : cardOrder)
    {
        for (const auto& effect : card->effects)
        {
            if (effect->triggered(event))
            {
                stack.push_back(effect);
            }
        }
    }
}

void Game::solveEffects()
{
    // Resolve the effects in the queue
}

std::vector<std::shared_ptr<Event>> Game::getHistoryDifference(const std::vector<std::shared_ptr<Event>>& oldHistory)
{
    std::vector<std::shared_ptr<Event>> historyDiff;

    if (history.size() > oldHistory.size())
    {
        if (oldHistory.empty())
        {
            historyDiff = history;
        }
        else
        {
            auto oldHistoryEnd = std::find(history.begin(), history.end(), oldHistory.back());

            // Increment this iterator one time because otherwise
            // this iterators element is included when creating the new array
            oldHistoryEnd++;

            historyDiff = std::vector<std::shared_ptr<Event>>(oldHistoryEnd, history.end());
        }
    }

    return historyDiff;
}
