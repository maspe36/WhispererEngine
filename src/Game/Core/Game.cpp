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
#include "../../../include/Network/Message.h"
#include "../../../include/Network/Derived/StartGameMessage.h"
#include "../../../include/Network/Derived/StartTurnMessage.h"
#include "../../../include/Network/Derived/EndTurnMessage.h"
#include "../../../include/Game/Derived/Event/GameEvents/StartGameEvent.h"

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

void Game::eventHandler(Event event)
{
    history.push_back(std::make_shared<Event>(event));
    queueEffects(event);
    solveEffects();
}

void Game::queueEffects(Event event)
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
    eventHandler(startGameEvent);
    sendStartGameMessage();
}

void Game::changeTurn()
{
    // Check for end turn effects

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

    sendTurnMessage();
}

Game::Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server)
        : players(std::move(players)), server(std::move(server))
{
}

Game::~Game()
= default;

void Game::sendStartGameMessage()
{
    for (const auto& player : players)
    {
        StartGameMessage startGameMessage(player, shared_from_this());
        player->client->write(startGameMessage.getJSON());
    }
}

void Game::sendTurnMessage()
{
    for (const auto& player : players)
    {
        if (activePlayer == player)
        {
            StartTurnMessage startTurnMessage(shared_from_this(), player);
            player->client->write(startTurnMessage.getJSON());
        }
        else
        {
            EndTurnMessage endTurnMessage;
            player->client->write(endTurnMessage.getJSON());
        }
    }
}
