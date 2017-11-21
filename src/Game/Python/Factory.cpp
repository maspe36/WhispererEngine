//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Python/Factory.h"
#include <iostream>

Card *Factory::createCard(std::string name)
{
    return nullptr;
}

Factory::Factory()
        : version(""), interpreter{}
{
    std::cout << "Factory Started" << std::endl;
    std::cout << "Using Python: " << Py_GetVersion() << std::endl;

    updateVersion();
}

/* Once the interpreter is started, automatically detect and fill the version */
void Factory::updateVersion()
{
    pybind11::module platform  = pybind11::module::import("platform");
    auto python_version = platform.attr("python_version")();

    auto version_string = python_version.cast<std::__cxx11::string>();
    version = Version(version_string);
}

Factory::~Factory()
= default;
