//
// Created by Sam on 3/18/2018.
//

#include "../../../../include/Game/Derived/Containers/Graveyard.h"
#include "../../../../include/Game/Core/Card.h"

json Graveyard::getJSON()
{
    std::vector<json> graveyardJSON;

    for (const auto& card : cards)
    {
        graveyardJSON.push_back(card->getJSON());
    }

    return graveyardJSON;
}

Graveyard::Graveyard()
= default;

Graveyard::~Graveyard()
= default;
