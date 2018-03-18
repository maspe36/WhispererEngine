//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CONSTANT_H
#define WHISPERERENGINE_CONSTANT_H


#include "../../Core/Card.h"

/* Represents the permanent, constant. */
class Constant
        : public Card
{
public:
    Constant(std::string name, std::string text, Mana mana);
    ~Constant();
};


#endif //WHISPERERENGINE_CONSTANT_H
