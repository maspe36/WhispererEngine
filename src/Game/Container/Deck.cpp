//
// Created by Sam on 3/1/2018.
//

#include <random>
#include <utility>

#include "../../../include/Game/Container/Deck.h"
#include "../../../include/Game/Card.h"

json Deck::getJSON()
{
    std::vector<json> jsonCards;

    for (const auto &card : cards)
    {
        jsonCards.push_back(card->getJSON());
    }

    json rawJSON;

    rawJSON["id"] = id;
    rawJSON["name"] = name;
    rawJSON["cards"] = jsonCards;

    return rawJSON;
}

std::shared_ptr<Card> Deck::draw()
{
    if (!cards.empty())
    {
        auto card = cards.front();
        cards.erase(cards.begin());

        return card;
    }
}

Deck::Deck(std::string deckID, std::vector<std::shared_ptr<Card>> cards)
        : id(std::move(deckID)), Container(cards)
{
    setClassNames();
}

Deck::Deck(std::string deckName, std::string deckID, std::vector<std::shared_ptr<Card>> cards)
        : name(std::move(deckName)), id(std::move(deckID)), Container(cards)
{
    setClassNames();
}

void Deck::setClassNames()
{
    for (auto const& card : cards)
    {
        classNames.push_back(card->pythonName);
    }
}

Deck::Deck()
= default;

Deck::~Deck()
= default;
