//
// Created by Sam on 3/18/2018.
//

#include "../../../include/Network/Derived/CardMovedMessage.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Core/Container.h"
#include "../../../include/Game/Core/Player.h"

CardMovedMessage::CardMovedMessage(const std::shared_ptr<Container> &origin,
                                   const std::shared_ptr<Container> &destination,
                                   const std::shared_ptr<Card> &card)
        : origin(origin), destination(destination), card(card), playerTag(card->player->tag)
{
}

CardMovedMessage::~CardMovedMessage()
= default;
