//
// Created by Sam Privett on 11/13/2017.
//

#include "../Core/Card.h"
#include "../Core/Mana.h"
#include "../Core/Player.h"
#include "../Core/Effect.h"
#include "../Core/Modifier.h"
#include "../Derived/Card/Constant.h"
#include "../Derived/Card/Creature.h"

#include <pybind11/embed.h>

namespace py = pybind11;

PYBIND11_EMBEDDED_MODULE(Whisperer, m) {
    py::class_<Card, std::shared_ptr<Card>> (m, "Card")
        .def(py::init<const std::string &, const std::string &, const Mana &>(),
            py::arg("name"), py::arg("text"), py::arg("mana"))
        .def_readwrite("name", &Card::name)
        .def_readwrite("text", &Card::text)
        .def_readwrite("mana", &Card::mana)
        .def_readwrite("player", &Card::player)
        .def_readwrite("effects", &Card::effects)
        .def_readwrite("modifiers", &Card::modifiers);

    py::class_<Constant, Card, std::shared_ptr<Constant>> (m, "Constant")
        .def(py::init<const std::string &, const std::string &, const Mana &>(),
             py::arg("name"), py::arg("text"), py::arg("mana"));

    py::class_<Creature, Card, std::shared_ptr<Creature>> (m, "Creature")
            .def(py::init<const std::string &, const std::string &, const Mana &, const int &, const int &>(),
                 py::arg("name"), py::arg("text"), py::arg("mana"), py::arg("attackStat"), py::arg("defenseStat"))
            .def_readwrite("attackStat", &Creature::attackStat)
            .def_readwrite("defenseStat", &Creature::defenseStat)
            .def_readwrite("attacks", &Creature::attacks)
            .def_readwrite("remainingAttacks", &Creature::remainingAttacks);

    py::class_<Mana> (m, "Mana")
            .def(py::init<const int &, const int &, const int &, const int &, const int &, const int &>(),
                 py::arg("black") = 0,
                 py::arg("blue") = 0,
                 py::arg("brown") = 0,
                 py::arg("green") = 0,
                 py::arg("red") = 0,
                 py::arg("white") = 0)
            .def_readwrite("black", &Mana::black)
            .def_readwrite("blue", &Mana::blue)
            .def_readwrite("brown", &Mana::brown)
            .def_readwrite("green", &Mana::green)
            .def_readwrite("red", &Mana::red)
            .def_readwrite("white", &Mana::white)
            .def("payMana", &Mana::payMana);
}
