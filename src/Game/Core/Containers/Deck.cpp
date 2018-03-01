//
// Created by Sam on 3/1/2018.
//

#include <utility>

#include "../../../../include/Game/Core/Containers/Deck.h"

json Deck::getJSON()
{
    return Exportable::getJSON();
}

Deck::Deck(std::vector<std::shared_ptr<Card>> cards)
        : cards(std::move(cards))
{
}

Deck::~Deck()
= default;
