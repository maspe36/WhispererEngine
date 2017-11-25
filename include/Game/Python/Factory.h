//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_FACTORY_H
#define WHISPERERENGINE_FACTORY_H


#include "../../../include/Game/Python/Version.h"

class Card;

namespace pybind11
{
    class scoped_interpreter;
};

/* Hanldes all python card creation. */
class Factory
{
public:
    Version version;

    std::shared_ptr<Card> createCard(std::string name);

    Factory();
    ~Factory();

private:
    pybind11::scoped_interpreter* interpreter;

    void updateVersion();
};


#endif //WHISPERERENGINE_FACTORY_H
