//
// Created by Sam on 3/28/2018.
//

#include "../../../../include/Network/Response/Game/DrawMessage.h"
#include "../../../../include/Game/Card.h"
#include "../../../../include/Game/Player.h"

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

DrawMessage::DrawMessage(DrawEvent drawEvent)
        : cards(drawEvent.cards)
{
    rawJSON[TYPE_KEY] = Message::DRAW_CARD;
    rawJSON[DATA_KEY]["playerTag"] = drawEvent.toPlayer->tag;
}

DrawMessage::~DrawMessage()
= default;
