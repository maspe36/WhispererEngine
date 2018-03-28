//
// Created by Sam on 3/28/2018.
//

#include "../../../include/Network/Derived/DrawMessage.h"
#include "../../../include/Game/Core/Card.h"

void DrawMessage::toOpponent()
{
    rawJSON[DATA_KEY]["cardsCount"] = cards.size();
}

void DrawMessage::toSelf()
{
    json cardsJSON;

    for (const auto& card : cards)
    {
        cardsJSON.push_back(card->getJSON());
    }

    rawJSON[DATA_KEY]["cards"] = cardsJSON;
}

DrawMessage::DrawMessage(std::shared_ptr<Game> game, std::vector<std::shared_ptr<Card>> cards, std::shared_ptr<Player> toPlayer)
        : cards(cards)
{
    rawJSON[TYPE_KEY] = Message::DRAW_CARD;
}

DrawMessage::~DrawMessage()
= default;
