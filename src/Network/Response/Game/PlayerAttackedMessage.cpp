//
// Created by Sam on 3/19/2018.
//

#include "../../../../include/Network/Response/Game/PlayerAttackedMessage.h"
#include "../../../../include/Game/Card.h"

PlayerAttackedMessage::PlayerAttackedMessage(PlayerAttackedEvent playerAttackedEvent)
{
    auto card = playerAttackedEvent.card;

    rawJSON[TYPE_KEY] = Message::PLAYER_ATTACKED;
    rawJSON[DATA_KEY]["cardTag"] = card->tag;
}

PlayerAttackedMessage::~PlayerAttackedMessage()
= default;
