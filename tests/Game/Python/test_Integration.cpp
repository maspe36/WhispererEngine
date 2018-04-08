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

TEST_CASE("shared_ptr Downcasting")
{
    Factory factory;

    py::module::import("sys").attr("path").cast<py::list>().append("../tests/Game");

    SECTION("shared_ptr<Card> -> shared_ptr<Creature>")
    {
        const std::string name = "Azar";

        std::shared_ptr<Card> card = factory.createCard(name);
        std::shared_ptr<Creature> creature = std::dynamic_pointer_cast<Creature>(card);
        REQUIRE(&creature != nullptr);
    }
}
