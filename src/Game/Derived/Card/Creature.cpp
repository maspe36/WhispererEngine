//
// Created by Sam on 9/25/2017.
//

#include "../../../../include/Game/Derived/Card/Creature.h"
#include <utility>


Creature::Creature(std::string name, std::string text, Mana mana, int attackStat, int defenseStat)
        : Card(std::move(name), std::move(text), mana),
          attackStat(attackStat), defenseStat(defenseStat), attacks(0), remainingAttacks(0)
{

}

Creature::~Creature()
= default;
