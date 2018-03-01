//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Derived/Card/Creature.h"
#include "../../../include/Game/Python/Factory.h"

TEST_CASE("Export Creature")
{
    Factory factory;

    std::shared_ptr<Card> card = factory.createCard("Azar");
    auto creature = std::dynamic_pointer_cast<Creature>(card);

    auto result = creature->getJSON();

    REQUIRE(result["name"] == creature->name);
    REQUIRE(result["text"] == creature->text);
    REQUIRE(result["tag"] == creature->tag);
    REQUIRE(result["mana"]["black"] == creature->mana.black);
    REQUIRE(result["mana"]["blue"]  == creature->mana.blue);
    REQUIRE(result["mana"]["brown"] == creature->mana.brown);
    REQUIRE(result["mana"]["green"] == creature->mana.green);
    REQUIRE(result["mana"]["red"] == creature->mana.red);
    REQUIRE(result["mana"]["white"] == creature->mana.white);

    REQUIRE(result["attackStat"] == creature->attackStat);
    REQUIRE(result["defenseStat"] == creature->defenseStat);
    REQUIRE(result["attacks"] == creature->attacks);
    REQUIRE(result["remainingAttacks"] == creature->remainingAttacks);

    std::cout << result.dump() << std::endl;
}
