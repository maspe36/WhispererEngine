//
// Created by Sam on 3/19/2018.
//

#include "../../../include/Network/Derived/PlayerAttackedMessage.h"
#include "../../../include/Game/Core/Card.h"

PlayerAttackedMessage::PlayerAttackedMessage(std::shared_ptr<Game> game, std::shared_ptr<Card> card)
{
    rawJSON[TYPE_KEY] = Message::PLAYER_ATTACKED;
    rawJSON[DATA_KEY]["cardTag"] = card->tag;
}

PlayerAttackedMessage::~PlayerAttackedMessage()
= default;
