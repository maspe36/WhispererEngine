//
// Created by Sam on 3/1/2018.
//

#include "../../../../include/Game/Core/Containers/Hand.h"
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

std::shared_ptr<Card> Hand::findCard(const std::string &tag)
{
    for (const auto& card : cards)
    {
        if (card->tag == tag)
        {
            return card;
        }
    }
}

void Hand::addCard(std::shared_ptr<Card> card)
{
    cards.push_back(card);
}

int Hand::count()
{
    return cards.size();
}

Hand::Hand()
= default;

Hand::~Hand()
= default;
