//
// Created by Sam on 10/7/2017.
//

#include "../../../build/catch-src/include/catch.hpp"

#include "../../../include/Game/Core/Mana.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Derived/Card/Constant.h"
#include "../../../include/Game/Derived/Card/Creature.h"

#include <pybind11/embed.h>

namespace py = pybind11;

TEST_CASE("Create cards from modules")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game/Core");

    SECTION("Create a card")
    {
        const std::string name = "testCard";
        const std::string text = "An empty test card";
        Mana mana(0, 0, 0, 0, 1, 0);

        py::object card = factory.createPyCard(name);
        auto base = card.cast<Card*>();

        REQUIRE(base->name == name);
        REQUIRE(base->text == text);
        REQUIRE(base->mana == mana);
    }

    SECTION("Create a constant")
    {
        const std::string name = "testConstant";
        const std::string text = "An empty test constant";
        Mana mana(1, 0, 0, 0, 0, 0);

        py::object card = factory.createPyCard(name);
        auto constant = card.cast<Constant*>();

        REQUIRE(constant->name == name);
        REQUIRE(constant->text == text);
        REQUIRE(constant->mana == mana);
    }

    SECTION("Create a creature")
    {
        const std::string name = "testCreature";
        const std::string text = "An empty test creature";
        Mana mana(1, 0, 0, 0, 0, 0);

        py::object card = factory.createPyCard(name);
        auto creature = card.cast<Creature*>();

        REQUIRE(creature->name == name);
        REQUIRE(creature->text == text);
        REQUIRE(creature->mana == mana);

        REQUIRE(creature->attackStat == 2);
        REQUIRE(creature->defenseStat == 1);
        REQUIRE(creature->attacks == 0);
        REQUIRE(creature->remainingAttacks == 0);
    }
}
