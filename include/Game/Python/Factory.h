//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_FACTORY_H
#define WHISPERERENGINE_FACTORY_H


#include "../../../include/Game/Python/Version.h"

#include <pybind11/embed.h>

namespace py = pybind11;

class Card;

/* Hanldes all python card creation. */
class Factory
{
public:
    Version version;

    Card* createCard(std::string name);

    Factory();
    ~Factory();

private:
    py::scoped_interpreter interpreter;

    void updateVersion();
};


#endif //WHISPERERENGINE_FACTORY_H
