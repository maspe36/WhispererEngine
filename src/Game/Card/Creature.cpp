//
// Created by Sam on 9/25/2017.
//

#include "../../../include/Game/Card/Creature.h"
#include "../../../include/Game/Player.h"


json Creature::getJSON()
{
    auto rawJSON = Card::getJSON();

    rawJSON["attackStat"] = attackStat;
    rawJSON["defenseStat"] = defenseStat;
    rawJSON["availableAttacks"] = availableAttacks;
    rawJSON["usedAttacks"] = usedAttacks;
    rawJSON["attacks"] = attacks;

    return rawJSON;
}

void Creature::attack(const std::shared_ptr<Player>& player)
{
    if (canAttack())
    {
        player->health -= attackStat;
        availableAttacks++;
    }
}

void Creature::attack(const std::shared_ptr<Creature>& creature)
{
    if (canAttack())
    {
        creature->defenseStat -= defenseStat;
        availableAttacks++;
    }
}

Creature::Creature(std::string name, std::string text, Mana mana, int attackStat, int defenseStat)
        : Card(std::move(name), std::move(text), mana),
          attackStat(attackStat), defenseStat(defenseStat), availableAttacks(0), usedAttacks(0), attacks(1)
{
}

bool Creature::canAttack()
{
    // A creature can attack if it has attacked less than the number of attacks available to it
    // and if the number of available attacks is greater than 0
    return (usedAttacks < availableAttacks && availableAttacks > 0);
}

Creature::~Creature()
= default;
