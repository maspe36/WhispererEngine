//
// Created by Sam on 9/25/2017.
//

#include "../../../../include/Game/Derived/Card/Creature.h"
#include "../../../../include/Game/Core/Player.h"


json Creature::getJSON()
{
    auto rawJSON = Card::getJSON();

    rawJSON["attackStat"] = attackStat;
    rawJSON["defenseStat"] = defenseStat;
    rawJSON["attacks"] = attacks;
    rawJSON["remainingAttacks"] = remainingAttacks;

    return rawJSON;
}

void Creature::attack(const std::shared_ptr<Player>& player)
{
    player->health -= attackStat;
}

void Creature::attack(const std::shared_ptr<Creature>& creature)
{
    creature->defenseStat -= defenseStat;
}

Creature::Creature(std::string name, std::string text, Mana mana, int attackStat, int defenseStat)
        : Card(std::move(name), std::move(text), mana),
          attackStat(attackStat), defenseStat(defenseStat), attacks(0), remainingAttacks(0)
{

}

Creature::~Creature()
= default;
