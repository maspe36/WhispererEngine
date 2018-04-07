//
// Created by Sam on 3/18/2018.
//

#include "../../../include/Game/Container/CreatureZone.h"
#include "../../../include/Game/Card/Creature.h"

CreatureZone::CreatureZone()
= default;

CreatureZone::~CreatureZone()
= default;

void CreatureZone::addCard(const std::shared_ptr<Card>& card)
{
    if (count() < sizeLimit)
    {
        Container::addCard(card);
    }
    else
    {
        throw std::runtime_error("You may not have more than 7 creatures in play");
    }
}
