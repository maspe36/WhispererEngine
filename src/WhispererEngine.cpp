//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"

#include <iostream>
#include "boost/thread.hpp"

int main()
{
    try
    {
        std::cout << "Initializing io_service..." << std::endl;
        boost::asio::io_service io_service;
        std::cout << "Starting server..." << std::endl;
        Server* server = new Server(io_service, 8888);
        std::cout << "Server started!" << std::endl;

        // Run the blocking io_service method run()
        boost::thread ioThread(
        boost::bind(&boost::asio::io_service::run, &io_service));

        // Consistently try to find games.
        while (true)
        {
            if (server->queue.size() >= 2)
            {
                // Get the two players who have been in queue the longest.
                std::cout << "Found 2 players in queue!" << std::endl;

                std::cout << server->queue.size() << " players in queue!" << std::endl;

                // Remove the first 2 players and check if they are still connected.
                Player* firstPlayer = server->queue.front();
                std::cout << firstPlayer->name << " was selected for a game..." << std::endl;
                server->queue.pop();

                Player* secondPlayer = server->queue.front();
                std::cout << secondPlayer->name << " was selected for a game..." << std::endl;
                server->queue.pop();

                std::cout << server->queue.size() << " players in queue!" << std::endl;

                std::cout << "Starting game between " << firstPlayer->name << " and " << secondPlayer->name << "..." << std::endl;

                Game* newGame = new Game({ firstPlayer, secondPlayer }, server);
                newGame->Start();
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
