//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Derived/Card/Constant.h"
#include "../../../include/Game/Core/Mana.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

Constant::Constant(std::string name, std::string text, Mana *mana) : Card(std::move(name), std::move(text), mana)
{
}

Constant::~Constant()
= default;

PYBIND11_MODULE(Constant, m) {
    py::class_<Constant, Card> (m, "Constant")
        .def(py::init<const std::string &, const std::string &, Mana*>(),
                py::arg("name"), py::arg("text"), py::arg("mana"));
}