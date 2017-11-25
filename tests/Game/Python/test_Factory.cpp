//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Derived/Card/Creature.h"
#include "../../../include/Game/Core/Mana.h"
#include "../../../include/Game/Core/Card.h"

TEST_CASE("Create factory")
{
    Factory factory;

    SECTION("Verify minimum python version")
    {
        std::string minimumVersion = "2.7";
        bool versionCheck = Version(minimumVersion) < factory.version;
        REQUIRE(versionCheck);
    }

    SECTION("Verify expected python version")
    {
        std::string expectedVersion = "3.6.3";
        bool versionCheck = Version(expectedVersion) == factory.version;

        if (!versionCheck)
        {
            FAIL_CHECK("Unexpected python version, expected " + expectedVersion +
                               " but factory's interpreter is running " + factory.version.toString());
        }
    }
}

TEST_CASE("Create a card")
{
    Factory factory;

    SECTION("Create a card")
    {
        std::shared_ptr<Card> creature = factory.createCard("Azar");
        REQUIRE(creature->name == "Azar");
        REQUIRE(creature->text == "The first Whisperer card!");
        REQUIRE(creature->mana->black == 0);
        REQUIRE(creature->mana->blue == 0);
        REQUIRE(creature->mana->brown == 0);
        REQUIRE(creature->mana->green == 0);
        REQUIRE(creature->mana->red == 1);
        REQUIRE(creature->mana->white == 0);
        std::cout << "Done testing" << std::endl;
    }
}
