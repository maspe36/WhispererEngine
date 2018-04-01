//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Card.h"
#include "../include/Game/Game.h"
#include "../include/Game/Player.h"
#include "../include/Game/Python/Factory.h"
#include "../include/Game/Card/Creature.h"
#include "../include/Network/Server.h"

#include <pybind11/embed.h>

void listClients(const std::shared_ptr<Server> &server);

void listPlayers(const std::shared_ptr<Server> &server);

void listGames(const std::shared_ptr<Server> &server);

namespace py = pybind11;


void commandListen(std::shared_ptr<Server> server)
{
    std::__cxx11::string line;
    while (getline(std::cin, line) && line != "quit")
    {
        if (line == "memes")
        {
            auto card = server->factory.createCard("Azar");
            auto creature = std::dynamic_pointer_cast<Creature>(card);

            std::cout << creature->getJSON().dump(4) << std::endl;
        }
        else if (line == "list")
        {
            listClients(server);
            std::cout << "--------------------------------------------------" << std::endl;
            listPlayers(server);
            std::cout << "--------------------------------------------------" << std::endl;
            listGames(server);
            std::cout << "--------------------------------------------------" << std::endl;
        }
        else
        {
            std::cout << "Unknown command: '" << line << "'" << std::endl;
        }
    }

    std::cout << "Shutting down..." << std::endl;
    server->stop();
    std::cout << "Bye!" << std::endl;
}

void listGames(const std::shared_ptr<Server> &server)
{
    for (const auto &game : server->games)
            {
                for (const auto& player : game->players)
                {
                    if (!player->name.empty())
                    {
                        std::cout << player->name << std::endl;
                    }
                }
            }
    std::cout << server->games.size() << " active game(s)" << std::endl;
}

void listPlayers(const std::shared_ptr<Server> &server)
{
    for (const auto &player : server->queue)
            {
                if (!player->name.empty())
                {
                    std::cout << player->name << std::endl;
                }
            }
    std::cout << server->queue.size() << " player(s) in queue" << std::endl;
}

void listClients(const std::shared_ptr<Server> &server)
{
    for (const auto &client : server->clients)
            {
                if (!client->name.empty())
                {
                    std::cout << client->name << std::endl;
                }
            }
    std::cout << server->clients.size() << " client(s) connected" << std::endl;
}

int main(int argc, const char* argv[])
{
    bool process = false;

    for(int i = 0; i < argc; ++i)
    {
        if(std::string(argv[i]) == "-process")
        {
            process = true;
        }
    }

    auto server = std::make_shared<Server>(8888);
    server->start();

    if (process)
    {
        while(true){}
    }
    else
    {
        commandListen(server);
    }
}
