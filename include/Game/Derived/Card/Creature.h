//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_CREATURE_H
#define WHISPERERENGINE_CREATURE_H


#include "../../Core/Card.h"

/* Represents the permanent, creature. */
class Creature
        : public Card
{
public:
    int attackStat;
    int defenseStat;
    int availableAttacks;
    int usedAttacks;
    int attacks;

    json getJSON() override;

    void attack(const std::shared_ptr<Player>& player);
    void attack(const std::shared_ptr<Creature>& creature);
    bool canAttack();

    Creature(std::string name, std::string text, Mana mana, int attackStat, int defenseStat);
    ~Creature();
};


#endif //WHISPERERENGINE_CREATURE_H
