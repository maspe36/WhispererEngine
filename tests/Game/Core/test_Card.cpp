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

TEST_CASE("Get C++ card from python")
{
    Factory factory;

    py::module whispererModule = py::module::import("Whisperer");

    // Construct a red card called 'Fire Boy' that costs 1 red mana
    Mana mana(0, 0, 0, 0, 1, 0);
    const std::string name = "Fire Boy";
    const std::string text = "A fired boy";
    py::object card = whispererModule.attr("Card")(name, text, mana);

    auto *cppCard = card.cast<Card*>();

    REQUIRE_FALSE(cppCard == nullptr);
    REQUIRE(cppCard->name == name);
    REQUIRE(cppCard->text == text);
    REQUIRE(cppCard->mana.black == 0);
    REQUIRE(cppCard->mana.blue == 0);
    REQUIRE(cppCard->mana.brown == 0);
    REQUIRE(cppCard->mana.green == 0);
    REQUIRE(cppCard->mana.red == 1);
    REQUIRE(cppCard->mana.white == 0);
}


TEST_CASE("Polymorphic up and down casting")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game/Core");

    SECTION("Constant up and down casting")
    {
        const std::string name = "testConstant";

        py::object card = factory.createCard(name);
        auto constant = card.cast<Constant*>();

        auto tempBase = dynamic_cast<Card*>(constant);
        REQUIRE(tempBase != nullptr);

        std::cout << "Up Casted Constant* to Card*" << std::endl;

        auto tempConstant = dynamic_cast<Constant*>(tempBase);
        REQUIRE(tempConstant != nullptr);

        std::cout << "Down casted Card* to Constant*" << std::endl;
    }

    SECTION("Creature up and down casting")
    {
        const std::string name = "testCreature";

        py::object card = factory.createCard(name);
        auto creature = card.cast<Creature*>();

        auto tempBase = dynamic_cast<Card*>(creature);
        REQUIRE(tempBase != nullptr);

        std::cout << "Up Casted Creature* to Card*" << std::endl;

        auto tempCreature = dynamic_cast<Creature*>(tempBase);
        REQUIRE(tempCreature != nullptr);

        std::cout << "Down casted Card* to Creature*" << std::endl;
    }
}

TEST_CASE("Create cards from modules")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game/Core");

    SECTION("Create a card")
    {
        const std::string name = "testCard";
        const std::string text = "An empty test card";

        py::object card = factory.createCard(name);
        auto base = card.cast<Card*>();
        REQUIRE(base->name == name);
        REQUIRE(base->text == text);
        REQUIRE(base->mana.black == 0);
        REQUIRE(base->mana.blue == 0);
        REQUIRE(base->mana.brown == 0);
        REQUIRE(base->mana.green == 0);
        REQUIRE(base->mana.red == 1);
        REQUIRE(base->mana.white == 0);
    }

    SECTION("Create a constant")
    {
        const std::string name = "testConstant";
        const std::string text = "An empty test constant";

        py::object card = factory.createCard(name);
        auto constant = card.cast<Constant*>();
        REQUIRE(constant->name == name);
        REQUIRE(constant->text == text);
        REQUIRE(constant->mana.black == 1);
        REQUIRE(constant->mana.blue == 0);
        REQUIRE(constant->mana.brown == 0);
        REQUIRE(constant->mana.green == 0);
        REQUIRE(constant->mana.red == 0);
        REQUIRE(constant->mana.white == 0);
    }

    SECTION("Create a creature")
    {
        const std::string name = "testCreature";
        const std::string text = "An empty test creature";

        py::object card = factory.createCard(name);

        auto creature = card.cast<Creature*>();
        REQUIRE(creature->name == name);
        REQUIRE(creature->text == text);
        REQUIRE(creature->mana.black == 1);
        REQUIRE(creature->mana.blue == 0);
        REQUIRE(creature->mana.brown == 0);
        REQUIRE(creature->mana.green == 0);
        REQUIRE(creature->mana.red == 0);
        REQUIRE(creature->mana.white == 0);
        REQUIRE(creature->attackStat == 2);
        REQUIRE(creature->defenseStat == 1);
        REQUIRE(creature->attacks == 0);
        REQUIRE(creature->remainingAttacks == 0);
    }
}
