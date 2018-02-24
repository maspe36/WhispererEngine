//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Card.h"
#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Game/Python/Factory.h"
#include "../include/Game/Derived/Card/Creature.h"
#include "../include/Network/Server.h"

#include <pybind11/embed.h>

namespace py = pybind11;


void commandListen(Server* server)
{
    std::__cxx11::string line;
    while (getline(std::cin, line) && line != "quit")
    {
        if (line == "memes")
        {
            auto card = server->factory.createCard("Azar");
            auto creature = std::dynamic_pointer_cast<Creature>(card);

            std::cout << "Name: " << creature->name << std::endl;
            std::cout << "Tag: " << creature->tag << std::endl;
            std::cout << "Text: " << creature->text << std::endl;
            std::cout << "Attack: " << creature->attackStat << std::endl;
            std::cout << "Defense: " << creature->defenseStat << std::endl;
            std::cout << "Black: " << creature->mana.black << std::endl;
            std::cout << "Blue: " << creature->mana.blue << std::endl;
            std::cout << "Brown: " << creature->mana.brown << std::endl;
            std::cout << "Red: " << creature->mana.red << std::endl;
            std::cout << "Green: " << creature->mana.green << std::endl;
            std::cout << "White: " << creature->mana.white << std::endl;
        }
        else if (line == "list")
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
        else
        {
            std::cout << "Unknown command: '" << line << "'" << std::endl;
        }
    }

    std::cout << "Shutting down..." << std::endl;
    server->Stop();
    std::cout << "Bye!" << std::endl;
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

    auto* server = new Server(8888);
    server->Start();

    if (process)
    {
        while(true){}
    }
    else
    {
        commandListen(server);
    }
}
