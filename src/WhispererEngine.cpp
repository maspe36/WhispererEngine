//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"

#include <iostream>
#include <boost/asio/io_service.hpp>
#include <boost/thread.hpp>

int main()
{
    try
    {
        std::cout << "Initializing server..." << std::endl;
        Server* server = new Server(8888);
        std::cout << "Starting server..." << std::endl;
        server->Start();
        std::cout << "Server started!" << std::endl;

        while(true)
        {
            // Blocking code until the io_service thread is figured out
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
