//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Python/Module.h"
#include "../../../include/Game/Python/Version.h"

#include "pybind11/eval.h"

namespace py = pybind11;

std::shared_ptr<Card> Factory::createCard(const std::string &name)
{
    py::object pyCard = createPyCard(name);

    auto card = pyCard.cast<std::shared_ptr<Card>>();
    card->pythonName = name;
    return card;
}

pybind11::object Factory::createPyCard(const std::string &name)
{
    py::module scope = py::module::import("__main__");
    return scope.attr(name.c_str())();
}

void Factory::refreshCards()
{
    std::map<std::string, std::string> cardDict = database.getAllCards();

    for (auto const& item : cardDict)
    {
        auto script = item.second;
        py::exec(script);
    }
}

Factory::Factory()
        : version(nullptr), interpreter(new py::scoped_interpreter{})
{
    std::cout << "Factory Started" << std::endl;
    std::cout << "Using Python: " << Py_GetVersion() << std::endl;

    updateVersion();

    py::module::import("sys").attr("path").cast<py::list>().append("../cards");
    refreshCards();
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
