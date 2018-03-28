//
// Created by Sam on 12/4/2017.
//

#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Card.h"
#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Card/Constant.h"
#include "../../../include/Game/Card/Creature.h"

#include <pybind11/embed.h>

namespace py = pybind11;


TEST_CASE("Get C++ card from python")
{
    Factory factory;

    py::module whispererModule = py::module::import("Whisperer");

    // Construct a red card called 'Fire Boy' that costs 1 red mana
    const std::string name = "Fire Boy";
    const std::string text = "A fired boy";
    Mana mana(0, 0, 0, 0, 1, 0);

    py::object card = whispererModule.attr("Card")(name, text, mana);
    auto *cppCard = card.cast<Card*>();

    REQUIRE_FALSE(cppCard == nullptr);
    REQUIRE(cppCard->name == name);
    REQUIRE(cppCard->text == text);
    REQUIRE(cppCard->mana == mana);
}

TEST_CASE("Polymorphic down casting")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game");

    SECTION("Card* to Constant*")
    {
        const std::string name = "testConstant";

        py::object card = factory.createPyCard(name);
        auto tempBase = card.cast<Card*>();

        auto tempConstant = dynamic_cast<Constant*>(tempBase);
        REQUIRE(tempConstant != nullptr);
    }

    SECTION("Card* to Creature*")
    {
        const std::string name = "testCreature";

        py::object card = factory.createPyCard(name);
        auto tempBase = card.cast<Card*>();

        auto tempCreature = dynamic_cast<Creature*>(tempBase);
        REQUIRE(tempCreature != nullptr);
    }
}

TEST_CASE("Polymorphic up casting")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game");

    SECTION("Constant* to Card*")
    {
        const std::string name = "testConstant";

        py::object card = factory.createPyCard(name);
        auto constant = card.cast<Constant*>();

        auto tempBase = dynamic_cast<Card*>(constant);
        REQUIRE(tempBase != nullptr);
    }

    SECTION("Creature* to Card*")
    {
        const std::string name = "testCreature";

        py::object card = factory.createPyCard(name);
        auto creature = card.cast<Creature*>();

        auto tempBase = dynamic_cast<Card*>(creature);
        REQUIRE(tempBase != nullptr);
    }
}

TEST_CASE("shared_ptr Downcasting")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game");

    SECTION("shared_ptr<Card> -> shared_ptr<Creature>")
    {
        const std::string name = "testCreature";

        std::shared_ptr<Card> card = factory.createCard(name);
        std::shared_ptr<Creature> creature = std::dynamic_pointer_cast<Creature>(card);
        REQUIRE(&creature != nullptr);
    }

    SECTION("shared_ptr<Card> -> shared_ptr<Constant>")
    {
        const std::string name = "testConstant";

        std::shared_ptr<Card> card = factory.createCard(name);
        std::shared_ptr<Constant> constant = std::dynamic_pointer_cast<Constant>(card);
        REQUIRE(&constant != nullptr);
    }
}
