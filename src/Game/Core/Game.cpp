//
// Created by Sam on 9/25/2017.
//

#include <random>
#include <utility>

#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Effect.h"
#include "../../../include/Network/Client.h"
#include "../../../include/Network/Server.h"
#include "../../../include/Game/Derived/Event/GameEvents/StartGameEvent.h"
#include "../../../include/Game/Derived/Event/GameEvents/StartTurnEvent.h"
#include "../../../include/Game/Derived/Event/GameEvents/EndTurnEvent.h"

std::vector<json> Game::getOpponentJSON(std::shared_ptr<Player> toPlayer)
{
    std::vector<json> opponentsJSON;

    for (const auto& player : players)
    {
        if (toPlayer != player)
        {
            auto opponentJSON = player->getOpponentState();
            opponentsJSON.push_back(opponentJSON);
        }
    }

    return opponentsJSON;
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
        player->board->deck->shuffle();
        player->draw(5);
    }

    std::shuffle(players.begin(), players.end(), std::mt19937(std::random_device()()));
    activePlayer = players.front();

    // Check for game start effects
    StartGameEvent startGameEvent(shared_from_this());
    eventHandler(std::make_shared<StartGameEvent>(startGameEvent));
}

void Game::changeTurn()
{
    // Check for end turn effects
    EndTurnEvent endTurnEvent(shared_from_this());
    eventHandler(std::make_shared<EndTurnEvent>(endTurnEvent));

    for (const auto& player : players)
    {
        if (player->tag != activePlayer->tag)
        {
            activePlayer = player;
            break;
        }
    }

    activePlayer->startTurn();

    // Check for start turn effects
    StartTurnEvent startTurnEvent(shared_from_this());
    eventHandler(std::make_shared<StartTurnEvent>(startTurnEvent));
}

Game::Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server)
        : players(std::move(players)), server(std::move(server))
{
}

Game::~Game()
= default;

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
