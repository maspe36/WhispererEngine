//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"

#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Python/Version.h"
#include "../../../include/Game/Derived/Card/Creature.h"
#include "../../../include/Game/Core/Mana.h"

TEST_CASE("Create factory")
{
    Factory factory;

    SECTION("Verify minimum python version")
    {
        std::string minimumVersion = "2.7";
        Version version(minimumVersion);
        bool versionCheck = version < *factory.version;
        REQUIRE(versionCheck);
    }

    SECTION("Verify expected python version")
    {
        std::string expectedVersion = "3.6.3";
        Version version(expectedVersion);
        bool versionCheck = version == *factory.version;

        if (!versionCheck)
        {
            FAIL_CHECK("Unexpected python version, expected " + expectedVersion +
                               " but factory's interpreter is running " + factory.version->toString());
        }
    }
}

TEST_CASE("Create a card")
{
    Factory factory;

    SECTION("Create a card")
    {
        std::shared_ptr<Card> card = factory.createCard("Azar");
        REQUIRE(card->name == "Azar");
        REQUIRE(card->text == "The first Whisperer card!");
        REQUIRE(card->mana.black == 0);
        REQUIRE(card->mana.blue == 0);
        REQUIRE(card->mana.brown == 0);
        REQUIRE(card->mana.green == 0);
        REQUIRE(card->mana.red == 1);
        REQUIRE(card->mana.white == 0);
        std::cout << "Done testing" << std::endl;
    }
}
