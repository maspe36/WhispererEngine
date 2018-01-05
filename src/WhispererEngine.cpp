//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"
#include "../include/Game/Python/Factory.h"
#include "../include/Game/Core/Card.h"
#include "../include/Game/Core/Mana.h"
#include "../include/Game/Derived/Card/Creature.h"

#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

int main()
{
    auto* server = new Server(8888);
    server->Start();
    Factory factory;

    // Exit if the user enters quit
    std::string line;
    while (std::getline(std::cin, line) && line != "quit")
    {
        if (line == "memes")
        {
            py::object card = factory.createCard("Azar");
            auto base = card.cast<Card*>();
            auto creature = dynamic_cast<Creature*>(base);

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
            std::cout << server->clients.size() << " clients connected" << std::endl;
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
