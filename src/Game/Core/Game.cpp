//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Network/Client.h"
#include "../../../include/Network/Server.h"
#include "../../../include/Network/Message.h"
#include "../../../include/Network/Derived/StartGameMessage.h"

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

    sendStartGameMessage();
}

Game::Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server)
        : players(std::move(players)), server(std::move(server))
{
}

Game::~Game()
= default;

void Game::sendStartGameMessage() const
{
    for (const auto& player : players)
    {
        StartGameMessage startGameMessage(player, players);
        player->client->write(startGameMessage.getJSON());
    }
}
