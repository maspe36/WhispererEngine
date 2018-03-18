//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_SPELL_H
#define WHISPERERENGINE_SPELL_H


#include "../../Core/Card.h"

/* Represents the card type, spell. */
class Spell
        : public Card
{
public:
    Spell(std::string name, std::string text, Mana *mana);
    ~Spell();
};


#endif //WHISPERERENGINE_SPELL_H
