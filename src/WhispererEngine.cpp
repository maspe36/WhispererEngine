//
// Created by Sam on 9/25/2017.
//

#include "../include/Game/Core/Game.h"
#include "../include/Game/Core/Player.h"
#include "../include/Network/Server.h"
#include "../include/Game/Python/Factory.h"
#include "../include/Game/Python/Version.h"

#include <iostream>

int main()
{
    std::shared_ptr<Factory> factory = std::make_shared<Factory>();
    std::string minimumVersion = "2.7";
    bool minimumCheck = Version(minimumVersion) < factory->version;
    std::string expectedVersion = "3.6.3";
    bool expectedCheck = Version(expectedVersion) == factory->version;

    std::cout << "minimumCheck: " << minimumCheck << std::endl;
    std::cout << "expectedCheck: " << expectedCheck << std::endl;

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
