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

TEST_CASE("Get CardIDs for Deck")
{
    // Don't fill this from a loop because this could change soon
    std::vector<std::string> expectedIDs = {"1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
                                            "1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
                                            "1", "1", "1", "1", "1", "1", "1", "1", "1", "1",
                                            "1", "1", "1", "1", "1", "1", "1", "1", "1", "1"};

    std::string userID = "1";
    std::string deckID = "1";

    Database database;
    std::vector<std::string> cardIDs = database.getDeckCards(userID, deckID);

    REQUIRE(cardIDs == expectedIDs);
}