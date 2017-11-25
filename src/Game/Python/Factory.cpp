//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Python/Module.h"
#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Core/Card.h"
#include <iostream>

#include <pybind11/embed.h>

namespace py = pybind11;

std::shared_ptr<Card> Factory::createCard(const std::string name)
{
    py::module cardModule = py::module::import(name.c_str());
    cardModule.reload();
    py::object card = cardModule.attr(name.c_str())();

    std::shared_ptr<Card> cppCard = std::make_shared<Card>(card.cast<Card>());
    return cppCard;
}

Factory::Factory()
        : version(""), interpreter(new py::scoped_interpreter{})
{
    std::cout << "Factory Started" << std::endl;
    std::cout << "Using Python: " << Py_GetVersion() << std::endl;

    updateVersion();

    py::module::import("sys").attr("path").cast<py::list>().append("../cards");
}

Factory::~Factory()
{
    delete interpreter;
}

/* Once the interpreter is started, automatically detect and fill the version */
void Factory::updateVersion()
{
    pybind11::module platform  = pybind11::module::import("platform");
    auto python_version = platform.attr("python_version")();

    auto version_string = python_version.cast<std::__cxx11::string>();
    version = Version(version_string);
}


