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
                    R"("User"."steamId" = '76561198026041712' AND "Deck"."id" = 1;)";

    Database database;
    std::string query = database.formatGetDeckCardsQuery(steamID, deckID);

    REQUIRE(query == expectedQuery.str());
}
