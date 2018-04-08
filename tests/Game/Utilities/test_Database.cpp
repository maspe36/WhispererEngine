//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Utilities/Database.h"
#include "../../../include/Game/Python/Factory.h"

TEST_CASE("Create database")
{
    Database database;
}

TEST_CASE("Verify get CardIDs for Deck SQL")
{
    std::string steamID = "76561198026041712";
    std::string deckID = "1";
    std::ostringstream expectedQuery;
    expectedQuery <<
                  "SELECT " <<
                    R"("Card"."PythonName" )" <<
                  "FROM " <<
                    R"(public."Card", )" <<
                    R"(public."CardToUser", )" <<
                    R"(public."CardUserToDeck", )" <<
                    R"(public."Deck", )" <<
                    R"(public."DeckToUser", )" <<
                    R"(public."User" )" <<
                  "WHERE " <<
                    R"("Card"."ID" = "CardToUser"."CardID" AND )" <<
                    R"("CardUserToDeck"."CardUserID" = "CardToUser"."ID" AND )" <<
                    R"("CardUserToDeck"."DeckID" = "Deck"."ID" AND )" <<
                    R"("Deck"."ID" = "DeckToUser"."DeckID" AND )" <<
                    R"("DeckToUser"."UserID" = "User"."ID" AND )" <<
                    R"("User"."ID" = "CardToUser"."UserID" AND )" <<
                    R"("User"."SteamID" = '76561198026041712' AND "Deck"."ID" = 1;)";

    Database database;
    std::string query = database.formatGetDeckCardsQuery(steamID, deckID);

    REQUIRE(query == expectedQuery.str());
}
