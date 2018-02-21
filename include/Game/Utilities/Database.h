//
// Created by Sam on 2/11/2018.
//

#ifndef WHISPERERENGINE_DATABASE_H
#define WHISPERERENGINE_DATABASE_H

#include <string>
#include <vector>
#include <libpq-fe.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Database
{
public:
    json config;

    std::vector<std::string> getDeckCards(std::string userID, std::string deckID);
    std::string formatGetDeckCardsQuery(std::string userID, std::string deckID);

    Database();
    ~Database();

private:
    std::string CONNECTION_INFO;
    PGconn* connection;

    PGresult* result;
    void initializeConfig();
    void initializeConnection();
};


#endif //WHISPERERENGINE_DATABASE_H
