//
// Created by Sam on 2/11/2018.
//

#ifndef WHISPERERENGINE_DATABASE_H
#define WHISPERERENGINE_DATABASE_H

#include <string>
#include <vector>
#include <libpq-fe.h>
#include <nlohmann/json.hpp>
#include "../Container/Deck.h"

using json = nlohmann::json;

class Factory;

class Database
{
public:
    json config;

    void setupUser(const std::string& steamID);

    std::vector<std::string> getDeckCards(const std::string& steamID, const std::string& deckID);
    std::string formatGetDeckCardsQuery(const std::string& steamID, const std::string& deckID);

    std::map<std::string, Deck> getAllDeckCards(const std::string& steamID, Factory* factory);
    std::string formatGetAllDecksAndCardsQuery(const std::string& steamID);

    bool isNewSteamID(const std::string& steamID);
    std::string formatIsNewSteamIDQuery(const std::string& steamID);


    void createUser(const std::string& steamID);
    std::string formatCreateUserQuery(const std::string& steamID);

    void giveCards(const std::string& steamID);
    std::string formatGiveCardsQuery(const std::string& steamID);

    void createDeckFor(const std::string& steamID);
    std::string formatCreateDeckForQuery(const std::string& steamID);

    void createFirstTimeDeck(const std::string& steamID);
    std::string formatCreateFirstTimeDeck(const std::string& steamID);

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
