//
// Created by Sam on 9/25/2017.
//

#include <utility>

#include "../../../include/Game/Core/Card.h"

void Card::addEffect(Effect *effect)
{
    effects.push_back(effect);
}

void Card::addModifier(Modifier *modifier)
{
    modifiers.push_back(modifier);
}

Card::Card(std::string name, std::string text, Mana *mana)
        : name(std::move(name)), text(std::move(text)), mana(mana)
{
}

Card::~Card()
= default;
