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
    std::string userID = "1";
    std::string deckID = "1";
    std::string expectedQuery = "SELECT \n"
                                    "  \"Card\".\"ID\"\n"
                                "FROM \n"
                                    "  public.\"Card\", \n"
                                    "  public.\"CardToUser\", \n"
                                    "  public.\"CardUserToDeck\", \n"
                                    "  public.\"Deck\", \n"
                                    "  public.\"DeckToUser\", \n"
                                    "  public.\"User\"\n"
                                "WHERE \n"
                                    "  \"Card\".\"ID\" = \"CardToUser\".\"CardID\" AND\n"
                                    "  \"CardUserToDeck\".\"CardUserID\" = \"CardToUser\".\"ID\" AND\n"
                                    "  \"CardUserToDeck\".\"DeckID\" = \"Deck\".\"ID\" AND\n"
                                    "  \"Deck\".\"ID\" = \"DeckToUser\".\"DeckID\" AND\n"
                                    "  \"DeckToUser\".\"UserID\" = \"User\".\"ID\" AND\n"
                                    "  \"User\".\"ID\" = \"CardToUser\".\"UserID\" AND \n"
                                    "  \"User\".\"ID\" = 1 AND \"Deck\".\"ID\" = 1;";

    Database database;
    std::string query = database.formatGetDeckCardsQuery(userID, deckID);

    REQUIRE(query == expectedQuery);
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