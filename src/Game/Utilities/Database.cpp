//
// Created by Sam on 2/11/2018.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <utility>
#include "../../../include/Game/Utilities/Database.h"
#include "../../../include/Game/Python/Factory.h"

void Database::setupUser(const std::string &steamID)
{
    createUser(steamID);
    giveCards(steamID);
    createFirstTimeDeck(steamID);
}

std::map<std::string, std::string> Database::getAllCards()
{
    std::map<std::string, std::string> cards;

    std::string query = formatGetAllCards();
    result = PQexec(connection, query.c_str());

    for (int i = 0; i < PQntuples(result); i++)
    {
        std::string className = PQgetvalue(result, i, 0);
        std::string script = PQgetvalue(result, i, 1);
        cards[className] = script;
    }

    return cards;
}

std::string Database::formatGetAllCards()
{
    std::ostringstream sqlStream;
    sqlStream << R"(SELECT "className", "script" FROM "Card")";

    return sqlStream.str();
}

std::vector<std::string> Database::getDeckCards(const std::string& steamID, const std::string& deckID)
{
    std::vector<std::string> rows;

    std::string query = formatGetDeckCardsQuery(steamID, deckID);
    result = PQexec(connection, query.c_str());

    for (int i = 0; i < PQntuples(result); i++)
    {
        rows.emplace_back(PQgetvalue(result, i, 0));
    }

    return rows;
}

std::string Database::formatGetDeckCardsQuery(const std::string& steamID, const std::string& deckID)
{
    std::ostringstream sqlStream;
    sqlStream <<
              "SELECT " <<
                R"("Card"."className" )" <<
              "FROM " <<
                R"(public."Card", )" <<
                R"(public."CardToUser", )" <<
                R"(public."CardUserToDeck", )" <<
                R"(public."Deck", )" <<
                R"(public."DeckToUser", )" <<
                R"(public."User" )" <<
              "WHERE " <<
                R"("Card"."id" = "CardToUser"."CardId" AND )" <<
                R"("CardUserToDeck"."CardToUserId" = "CardToUser"."id" AND )" <<
                R"("CardUserToDeck"."DeckId" = "Deck"."id" AND )" <<
                R"("Deck"."id" = "DeckToUser"."DeckId" AND )" <<
                R"("DeckToUser"."UserId" = "User"."id" AND )" <<
                R"("User"."id" = "CardToUser"."UserId" AND )" <<
                R"("User"."steamId" = ')" << steamID << R"(' AND "Deck"."id" = )" << deckID << ";";

    return sqlStream.str();
}

std::map<std::string, Deck> Database::getAllDeckCards(const std::string &steamID, Factory* factory)
{
    std::map<std::string, Deck> deckMap;

    std::string query = formatGetAllDecksAndCardsQuery(steamID);
    result = PQexec(connection, query.c_str());

    for (int i = 0; i < PQntuples(result); i++)
    {
        std::string name = PQgetvalue(result, i, 0);
        std::string id = PQgetvalue(result, i, 1);
        std::string className = PQgetvalue(result, i, 2);

        if (deckMap[name].name.empty())
        {
            deckMap[name].name = name;
        }

        if (deckMap[name].id.empty())
        {
            deckMap[name].id = id;
        }

        deckMap[name].cards.push_back(factory->createCard(className));
    }

    return deckMap;
}

std::string Database::formatGetAllDecksAndCardsQuery(const std::string &steamID)
{
    std::ostringstream sqlStream;
    sqlStream <<
              "SELECT " <<
              R"("Deck"."name", )" <<
              R"("Deck"."id", )" <<
              R"("Card"."className" )" <<
              "FROM " <<
              R"(public."Card", )" <<
              R"(public."CardToUser", )" <<
              R"(public."CardUserToDeck", )" <<
              R"(public."Deck", )" <<
              R"(public."DeckToUser", )" <<
              R"(public."User" )" <<
              "WHERE " <<
              R"("Card"."id" = "CardToUser"."CardId" AND )" <<
              R"("CardUserToDeck"."CardToUserId" = "CardToUser"."id" AND )" <<
              R"("CardUserToDeck"."DeckId" = "Deck"."id" AND )" <<
              R"("Deck"."id" = "DeckToUser"."DeckId" AND )" <<
              R"("DeckToUser"."UserId" = "User"."id" AND )" <<
              R"("User"."id" = "CardToUser"."UserId" AND )" <<
              R"("User"."steamId" = ')" << steamID << "';";

    return sqlStream.str();
}

bool Database::isNewSteamID(const std::string& steamID)
{
    std::string query = formatIsNewSteamIDQuery(steamID);

    std::cout << "Executing isNewSteamID..." << std::endl;
    std::cout << query << std::endl;

    result = PQexec(connection, query.c_str());

    std::string strCount;
    int count;
    for (int i = 0; i < PQntuples(result); i++)
    {
        strCount = PQgetvalue(result, i, 0);
    }

    count = stoi(strCount);

    return count == 0;
}

std::string Database::formatIsNewSteamIDQuery(const std::string& steamID)
{
    std::ostringstream sqlStream;
    sqlStream <<
              "SELECT " <<
              R"(COUNT("steamId"))" <<
              "FROM " <<
              R"(public."User" )" <<
              "WHERE " <<
              R"("steamId" = ')" << steamID << "';";

    return sqlStream.str();
}

void Database::createUser(const std::string &steamID)
{
    std::string query = formatCreateUserQuery(steamID);

    std::cout << "Executing createUser..." << std::endl;
    std::cout << query << "\n" << std::endl;

    result = PQexec(connection, query.c_str());
}

std::string Database::formatCreateUserQuery(const std::string &steamID)
{
    std::ostringstream sqlStream;
    sqlStream <<
        "INSERT INTO " <<
            R"("User" ("steamId"))" <<
        "VALUES('" << steamID << "')";

    return sqlStream.str();
}


void Database::giveCards(const std::string &steamID)
{
    std::string query = formatGiveCardsQuery(steamID);

    std::cout << "Executing giveCards..." << std::endl;
    std::cout << query << "\n" << std::endl;

    result = PQexec(connection, query.c_str());
}

std::string Database::formatGiveCardsQuery(const std::string &steamID)
{
    std::ostringstream sqlStream;
    sqlStream <<
        "DO $$ DECLARE i bigint; " <<
        "BEGIN " <<
            R"(FOR i IN 1..20 LOOP )" <<
                R"(INSERT INTO "CardToUser"("CardId", "UserId") SELECT "Card"."id", "User"."id" )" <<
                R"(FROM "Card", "User" WHERE "User"."steamId" = ')" << steamID << "'; " <<
            "END LOOP; " <<
        "END$$;";

    return sqlStream.str();
}

void Database::createDeckFor(const std::string &steamID)
{
    int deckID = createDeckAndGetID();
    std::string query = formatCreateDeckForQuery(steamID, deckID);

    std::cout << "Executing createDeckFor..." << std::endl;
    std::cout << query << "\n" << std::endl;

    result = PQexec(connection, query.c_str());
}

std::string Database::formatCreateDeckForQuery(const std::string &steamID, int deckID)
{
    std::ostringstream getUserIDSQL;
    getUserIDSQL <<
        R"(SELECT "id" )" <<
        R"(FROM public."User" )" <<
        R"(WHERE "steamId" = ')" << steamID << "'";

    std::ostringstream linkDeckToUserSQL;
    linkDeckToUserSQL <<
        R"(INSERT INTO "DeckToUser" ("UserId", "DeckId") )" <<
        "VALUES(" << "(" << getUserIDSQL.str() << ")" << ", (" << deckID << "))" ;

    return linkDeckToUserSQL.str();
}

void Database::createFirstTimeDeck(const std::string &steamID)
{
    createDeckFor(steamID);
    std::string query = formatCreateFirstTimeDeck(steamID);

    std::cout << "Executing createFirstTimeDeck..." << std::endl;
    std::cout << query << "\n" << std::endl;

    result = PQexec(connection, query.c_str());
}

std::string Database::formatCreateFirstTimeDeck(const std::string &steamID)
{
    std::ostringstream getFirstUserDeckIDSQL;
    getFirstUserDeckIDSQL <<
        R"(SELECT "Deck"."id" )" <<
        R"(FROM "Deck", "User", "DeckToUser" )" <<
        R"(WHERE "Deck"."id" = "DeckToUser"."DeckId" AND "User"."id" = "DeckToUser"."UserId" )" <<
        R"(AND "User"."steamId" = ')" << steamID << "' LIMIT 1";

    std::ostringstream getCardUserIDSQLStream;
    getCardUserIDSQLStream <<
        R"(SELECT "CardToUser"."id", ()" << getFirstUserDeckIDSQL.str() << ") " <<
        R"(FROM "User", "Card", "CardToUser" )" <<
        R"(WHERE "User"."id" = "CardToUser"."UserId" AND "Card"."id" = "CardToUser"."CardId" )" <<
        R"(AND "User"."steamId" = ')" << steamID << "' LIMIT 40";

    std::ostringstream createSQLStream;
    createSQLStream << R"(INSERT INTO "CardUserToDeck"("CardToUserId", "DeckId") )" << getCardUserIDSQLStream.str();

    return createSQLStream.str();
}

int Database::createDeckAndGetID()
{
    std::string query = formatCreateDeckAndGetIDQuery();

    std::cout << "Executing createDeckAndGetID..." << std::endl;
    std::cout << query << "\n" << std::endl;

    result = PQexec(connection, query.c_str());

    std::string strDeckID;
    int deckID;
    for (int i = 0; i < PQntuples(result); i++)
    {
        strDeckID = PQgetvalue(result, i, 0);
    }

    deckID = stoi(strDeckID);

    return deckID;
}

std::string Database::formatCreateDeckAndGetIDQuery()
{
    std::ostringstream createDeckSQL;
    createDeckSQL <<
                  R"(INSERT INTO "Deck" ("name"))" <<
                  "VALUES('" << "Starter Deck" << R"(') RETURNING "Deck"."id")";

    return createDeckSQL.str();
}

Database::Database()
        : result(nullptr)
{
    initializeConfig();
    CONNECTION_INFO = config["CONNECTION_INFO"];
    initializeConnection();
}

Database::~Database()
{
    PQfinish(connection);
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
