//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Core/Mana.h"
#include <pybind11/pybind11.h>

namespace py = pybind11;

void Mana::payMana(Mana *mana)
{
    black -= mana->black;
    blue -= mana->blue;
    brown -= mana->brown;
    green -= mana->green;
    red -= mana->red;
    white -= mana->white;
}

Mana::Mana(int black, int blue, int brown, int green, int red, int white)
        : black(black), blue(blue), brown(brown), green(green), red(red), white(white)
{
}

Mana::~Mana()
= default;

PYBIND11_MODULE(Mana, m) {
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