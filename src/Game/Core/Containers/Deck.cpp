//
// Created by Sam on 3/1/2018.
//

#include <utility>

#include "../../../../include/Game/Core/Containers/Deck.h"
#include "../../../../include/Game/Core/Card.h"

json Deck::getJSON()
{
    std::vector<json> jsonCards;

    for (const auto &card : cards)
    {
        jsonCards.push_back(card->getJSON());
    }

    json rawJSON;

    rawJSON["deckID"] = deckID;
    rawJSON["cards"] = jsonCards;

    return rawJSON;
}

Deck::Deck(std::string deckID, std::vector<std::shared_ptr<Card>> cards)
        : deckID(std::move(deckID)), cards(std::move(cards))
{
}

Deck::~Deck()
= default;
