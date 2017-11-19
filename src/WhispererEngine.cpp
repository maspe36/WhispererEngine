//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"

#include <iostream>

int main()
{
    std::cout << "Initializing server..." << std::endl;
    auto* server = new Server(8888);
    std::cout << "Starting server..." << std::endl;
    server->Start();
    std::cout << "Server started!" << std::endl;

    // Exit if the user enters quit
    std::string line;
    while (std::getline(std::cin, line) && line != "quit")
    {
        std::cout << "Unknown command: '" << line << "'" << std::endl;
    }

    std::cout << "Shutting down..." << std::endl;
    server->Stop();
    std::cout << "Bye!" << std::endl;
}
