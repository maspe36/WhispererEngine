//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Network/Client.h"

void Game::WritePlayers(const std::string &data)
{
    for (const auto& player : players)
    {
        player->client->write(data);
    }
}

Game::Game(std::vector<std::shared_ptr<Player>> players, std::shared_ptr<Server> server)
        : players(std::move(players)), server(std::move(server))
{
}

Game::~Game()
= default;
