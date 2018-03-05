//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Python/Module.h"
#include "../../../include/Game/Python/Version.h"

namespace py = pybind11;

std::shared_ptr<Card> Factory::createCard(const std::string &name)
{
    auto pyCard = Factory::createPyCard(name);
    auto card = pyCard.cast<std::shared_ptr<Card>>();
    return card;
}

py::object Factory::createPyCard(const std::string &name)
{
    py::module cardModule = py::module::import(name.c_str());
    cardModule.reload();
    py::object pyCard = cardModule.attr(name.c_str())();

    return pyCard;
}

std::vector<std::shared_ptr<Card>> Factory::createCards(std::vector<std::string> pythonNames)
{
    std::vector<std::shared_ptr<Card>> cards;

    for (const auto &name : pythonNames)
    {
        auto card = createCard(name);
        cards.push_back(card);
    }
}

Factory::Factory()
        : version(nullptr), interpreter(new py::scoped_interpreter{})
{
    std::cout << "Factory Started" << std::endl;
    std::cout << "Using Python: " << Py_GetVersion() << std::endl;

    updateVersion();

    py::module::import("sys").attr("path").cast<py::list>().append("../cards");
}

Factory::~Factory()
{
    delete interpreter;
    delete version;
}

/* Once the interpreter is started, automatically detect and fill the version */
void Factory::updateVersion()
{
    pybind11::module platform  = pybind11::module::import("platform");
    auto python_version = platform.attr("python_version")();

    auto version_string = python_version.cast<std::__cxx11::string>();
    version = new Version(version_string);
}
