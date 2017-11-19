//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Python/Factory.h"
#include <iostream>

Card *Factory::createCard(std::string name)
{
    return nullptr;
}

Factory::Factory() : interpreter()
{
    std::cout << "Factory Started" << std::endl;
    std::cout << "Using Python: " << Py_GetVersion() << std::endl;
}

Factory::~Factory()
= default;
