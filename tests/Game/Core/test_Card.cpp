//
// Created by Sam on 10/7/2017.
//

#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Core/Mana.h"
#include "../../../include/Game/Core/Card.h"
#include <iostream>
#include <pybind11/embed.h>

namespace py = pybind11;

TEST_CASE("Get C++ card from python")
{
    py::scoped_interpreter guard{};

    py::module whispererModule = py::module::import("Whisperer");

    // Construct a red card called 'Fire Boy' that costs 1 red mana
    auto* mana = new Mana(0, 0, 0, 0, 1, 0);
    const std::string name = "Fire Boy";
    const std::string text = "A fired boy";
    py::object card = whispererModule.attr("Card")(name, text, mana);

    auto *cppCard = card.cast<Card*>();

    REQUIRE(cppCard != nullptr);
    REQUIRE(cppCard->name == name);
    REQUIRE(cppCard->text == text);
    REQUIRE(cppCard->mana == mana);
}
