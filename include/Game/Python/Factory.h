//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_FACTORY_H
#define WHISPERERENGINE_FACTORY_H


#include <iostream>
#include <memory>
#include <vector>

class Card;
class Version;

namespace pybind11
{
    class scoped_interpreter;
    class object;
};

/* Hanldes all python card creation. */
class Factory
{
public:
    Version* version;

    std::shared_ptr<Card> createCard(const std::string &name);
    pybind11::object createPyCard(const std::string &name);

    Factory();
    ~Factory();

private:
    pybind11::scoped_interpreter* interpreter;

    void updateVersion();
};


#endif //WHISPERERENGINE_FACTORY_H
