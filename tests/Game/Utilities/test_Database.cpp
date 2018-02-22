//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Utilities/Database.h"

TEST_CASE("Create database")
{
    Database database;
}

TEST_CASE("Verify get CardIDs for Deck SQL")
{
    std::string userID = "STEAM_1:0:32887992";
    std::string deckID = "1";
    std::string expectedQuery = R"( SELECT 
                                        "Card"."PythonName"
                                    FROM
                                        public."Card", 
                                        public."CardToUser", 
                                        public."CardUserToDeck",
                                        public."Deck", 
                                        public."DeckToUser", 
                                        public."User"
                                    WHERE
                                        "Card"."ID" = "CardToUser"."CardID" AND
                                        "CardUserToDeck"."CardUserID" = "CardToUser"."ID" AND
                                        "CardUserToDeck"."DeckID" = "Deck"."ID" AND
                                        "Deck"."ID" = "DeckToUser"."DeckID" AND
                                        "DeckToUser"."UserID" = "User"."ID" AND
                                        "User"."ID" = "CardToUser"."UserID" AND
                                        "User"."SteamID" = 'STEAM_1:0:32887992' AND "Deck"."ID" = 1;)";

    Database database;
    std::string query = database.formatGetDeckCardsQuery(userID, deckID);

    REQUIRE(query == expectedQuery);
}

TEST_CASE("Get CardIDs for Deck")
{
    // Don't fill this from a loop because this could change soon
    std::vector<std::string> expectedNames = {"Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar",
                                              "Azar", "Azar", "Azar", "Azar", "Azar"};

    std::string userID = "STEAM_1:0:32887992";
    std::string deckID = "1";

    Database database;
    std::vector<std::string> cardIDs = database.getDeckCards(userID, deckID);

    REQUIRE(cardIDs == expectedIDs);
}