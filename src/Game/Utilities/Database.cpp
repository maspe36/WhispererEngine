//
// Created by Sam on 2/11/2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "../../../include/Game/Utilities/Database.h"

std::vector<std::string> Database::getDeckCards(std::string deckID)
{
    return std::vector<std::string>();
}

Database::Database()
{
    initializeConfig();
    CONNECTION_INFO = config["CONNECTION_INFO"];
    initializeConnection();
}

void Database::initializeConnection()
{
    connection = PQconnectdb(CONNECTION_INFO.c_str());
    if (PQstatus(connection) != CONNECTION_OK)
    {
        std::cout << "Connection to database failed: " << PQerrorMessage(connection) << std::endl;
    }
    else
    {
        std::cout << "Connected to " << CONNECTION_INFO << std::endl;
    }
}

void Database::initializeConfig()
{
    // Path is relative to the exe in the build folder. This should probably be updated at some point?
    std::ifstream dbfile("../dbconfig.json", std::ifstream::in);
    std::stringstream buffer;
    buffer << dbfile.rdbuf();
    std::string rawJSON = buffer.str();
    config = json::parse(rawJSON);
}

Database::~Database()
{
    PQfinish(connection);
}
