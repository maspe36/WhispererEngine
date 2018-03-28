//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Card/Constant.h"
#include "../../../include/Game/Mana.h"

Constant::Constant(std::string name, std::string text, Mana mana) : Card(std::move(name), std::move(text), mana)
{
}

Constant::~Constant()
= default;
