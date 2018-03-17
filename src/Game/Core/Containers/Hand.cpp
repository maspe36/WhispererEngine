//
// Created by Sam on 3/1/2018.
//

#include <utility>

#include "../../../../include/Game/Core/Containers/Hand.h"
#include "../../../../include/Game/Core/Card.h"
#include "../../../../include/Game/Core/Player.h"

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

    throw std::runtime_error("This card  (" + tag + ") is not present in players (" + player->tag + ") hand");
}

void Hand::addCard(std::shared_ptr<Card> card)
{
    cards.push_back(card);
}

void Hand::removeCard(std::shared_ptr<Card> card)
{
    cards.erase(std::find(cards.begin(), cards.end(), card));
}

int Hand::count()
{
    return cards.size();
}

Hand::Hand(const std::shared_ptr<Player>& player)
        : player(player)
{
}

Hand::~Hand()
= default;
