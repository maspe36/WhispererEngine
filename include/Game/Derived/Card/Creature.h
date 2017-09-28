//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CREATURE_H
#define WHISPERERENGINE_CREATURE_H


#include "../../Core/Card.h"

/* Represents the permanent, creature. */
class Creature : public Card
{
public:
    int attackStat;
    int defenseStat;
    int attacks;
    int remainingAttacks;

    Creature(std::string name, std::string text, Mana *mana, int attackStat, int defenseStat);
    ~Creature();
};


#endif //WHISPERERENGINE_CREATURE_H
