//
// Created by Sam Privett on 11/13/2017.
//

#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Core/Mana.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Effect.h"
#include "../../../include/Game/Core/Modifier.h"
#include "../../../include/Game/Derived/Card/Constant.h"

#include <pybind11/pybind11.h>

namespace py = pybind11;

PYBIND11_MODULE(Whisperer, m) {
    py::class_<Card> (m, "Card")
        .def(py::init<const std::string &, const std::string &, Mana*>(),
            py::arg("name"), py::arg("text"), py::arg("mana"))
        .def_readwrite("name", &Card::name)
        .def_readwrite("text", &Card::text)
        .def_readwrite("mana", &Card::mana)
        .def_readwrite("player", &Card::player)
        .def_readwrite("effects", &Card::effects)
        .def_readwrite("modifiers", &Card::modifiers)
        .def("addEffect", &Card::addEffect)
        .def("addModifier", &Card::addModifier);

    py::class_<Constant, Card> (m, "Constant")
        .def(py::init<const std::string &, const std::string &, Mana*>(),
             py::arg("name"), py::arg("text"), py::arg("mana"));

    py::class_<Mana> (m, "Mana")
            .def(py::init<const int &, const int &, const int &, const int &, const int &, const int &>(),
                 py::arg("black"), py::arg("blue"), py::arg("brown"), py::arg("green"), py::arg("red"), py::arg("white"))
            .def_readwrite("black", &Mana::black)
            .def_readwrite("blue", &Mana::blue)
            .def_readwrite("brown", &Mana::brown)
            .def_readwrite("green", &Mana::green)
            .def_readwrite("red", &Mana::red)
            .def_readwrite("white", &Mana::white)
            .def("payMana", &Mana::payMana);
}
