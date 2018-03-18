//
// Created by Sam on 3/1/2018.
//

#include <iostream>
#include "../../../../include/Game/Derived/Containers/Hand.h"
#include "../../../../include/Game/Core/Card.h"

json Hand::getJSON()
{
    std::vector<json> handJSON;

    for (auto const& card : cards)
    {
        handJSON.push_back(card->getJSON());
    }

    return handJSON;
}

std::shared_ptr<Card> Hand::getCard(const std::string &tag)
{
    for (const auto& card : cards)
    {
        if (card->tag == tag)
        {
            return card;
        }
    }

    throw std::runtime_error("No card with this tag (" + tag + ") was found");
}

void Hand::addCard(std::shared_ptr<Card> card)
{
    cards.push_back(card);
}

void Hand::removeCard(std::shared_ptr<Card> card)
{
    cards.erase(std::remove(cards.begin(), cards.end(), card));
}

int Hand::count()
{
    return cards.size();
}

Hand::Hand()
= default;

Hand::~Hand()
= default;
