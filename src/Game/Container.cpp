//
// Created by Sam on 3/18/2018.
//

#include "../../include/Game/Container.h"
#include "../../include/Game/Card.h"
#include <random>

json Container::getJSON()
{
    std::vector<json> containerJSON;

    for (const auto& card : cards)
    {
        containerJSON.push_back(card->getJSON());
    }

    return containerJSON;
}

std::shared_ptr<Card> Container::findCard(const std::string &tag)
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

int Container::count()
{
    return cards.size();
}

void Container::shuffle()
{
    std::shuffle(cards.begin(), cards.end(), std::mt19937(std::random_device()()));
}

void Container::addCard(const std::shared_ptr<Card>& card)
{
    cards.push_back(card);
}

void Container::removeCard(const std::shared_ptr<Card>& card)
{
    cards.erase(std::remove(cards.begin(), cards.end(), card));
}

Container::Container(const std::vector<std::shared_ptr<Card>> &cards)
        : cards(cards)
{
}

Container::Container()
= default;

Container::~Container()
= default;
