//
// Created by Sam on 10/7/2017.
//

#include "../../../build/catch-src/include/catch.hpp"

#include "../../../include/Game/Core/Mana.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Derived/Card/Constant.h"
#include "../../../include/Game/Derived/Card/Creature.h"
#include "../../../include/Game/Utilities/Database.h"

#include <pybind11/embed.h>

namespace py = pybind11;

TEST_CASE("Create deck")
{
    Database database;
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game/Core");

    std::vector<std::string> pythonNames = {"Azar", "Azar"};
    std::vector<std::shared_ptr<Card>> deck;

    for (const auto &name : pythonNames)
    {
        auto card = factory.createCard(name);
        deck.push_back(card);
    }

    for (const auto &card : deck)
    {
        std::cout << card->name << std::endl;
    }

    REQUIRE(deck.size() >= 2);
}
