//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_FACTORY_H
#define WHISPERERENGINE_FACTORY_H


#include "../../../include/Game/Python/Version.h"

#include <pybind11/embed.h>

namespace py = pybind11;

class Card;

/* Ignore the visibility warning from gcc
 * caused by having a library type as a class member */
#pragma GCC visibility push(hidden)

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
#pragma GCC visibility pop


#endif //WHISPERERENGINE_FACTORY_H
