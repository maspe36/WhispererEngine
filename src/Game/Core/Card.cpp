//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Core/Mana.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Core/Effect.h"
#include "../../../include/Game/Core/Modifier.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void Card::addEffect(Effect *effect)
{
    effects.push_back(effect);
}

void Card::addModifier(Modifier *modifier)
{
    modifiers.push_back(modifier);
}

Card::Card(std::string name, std::string text, Mana *mana)
        : name(std::move(name)), text(std::move(text)), mana(mana)
{
}

Card::~Card()
= default;

PYBIND11_MODULE(Card, m) {
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
}