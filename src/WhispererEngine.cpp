//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"
#include "../include/Game/Python/Factory.h"
#include "../include/Game/Core/Card.h"
#include "../include/Game/Core/Mana.h"

#include <iostream>

int main()
{
    std::cout << "Initializing server..." << std::endl;
    auto* server = new Server(8888);
    std::cout << "Starting server..." << std::endl;
    server->Start();
    std::cout << "Server started!" << std::endl;

    Factory factory;

    // Exit if the user enters quit
    std::string line;
    while (std::getline(std::cin, line) && line != "quit")
    {
        if (line == "memes")
        {
            std::shared_ptr<Card> card = factory.createCard("Azar");

            std::cout << "name: " << card->name << std::endl;
            std::cout << "text: " << card->text << std::endl;
            std::cout << "black: " << card->mana->black << std::endl;
            std::cout << "blue: " << card->mana->blue << std::endl;
            std::cout << "brown: " << card->mana->brown << std::endl;
            std::cout << "red: " << card->mana->red << std::endl;
            std::cout << "green: " << card->mana->green << std::endl;
            std::cout << "white: " << card->mana->white << std::endl;
        }
        std::cout << "Unknown command: '" << line << "'" << std::endl;
    }

    std::cout << "Shutting down..." << std::endl;
    server->Stop();
    std::cout << "Bye!" << std::endl;
}
