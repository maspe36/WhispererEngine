//
// Created by Sam on 3/19/2018.
//

#include "../../../../include/Game/Event/Player/PlayerAttackedEvent.h"
#include "../../../../include/Network/Message/PlayerAttackedMessage.h"
#include "../../../../include/Network/Client.h"

void PlayerAttackedEvent::sendMessage()
{
    PlayerAttackedMessage playerAttackedMessage(game, card);
    targetPlayer->client->write(playerAttackedMessage.getJSON());
}

PlayerAttackedEvent::PlayerAttackedEvent(const std::shared_ptr<Game> &game,
                                         const std::shared_ptr<Card> &card,
                                         const std::shared_ptr<Player> &targetPlayer)
        : Event(game), card(card), targetPlayer(targetPlayer)
{
}

PlayerAttackedEvent::~PlayerAttackedEvent()
= default;
