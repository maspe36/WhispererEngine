//
// Created by Sam on 3/18/2018.
//

#include "../../../../include/Game/Derived/Containers/CreatureZone.h"
#include "../../../../include/Game/Derived/Card/Creature.h"

json CreatureZone::getJSON()
{
    std::vector<json> creaturesJSON;

    for (const auto& card : cards)
    {
        creaturesJSON.push_back(card->getJSON());
    }

    return creaturesJSON;
}

CreatureZone::CreatureZone()
= default;

CreatureZone::~CreatureZone()
= default;
