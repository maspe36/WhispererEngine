//
// Created by Sam on 3/29/2018.
//

#include "../../../../include/Game/Event/Player/CreatureAttackedEvent.h"
#include "../../../../include/Network/Response/Game/CreatureAttackedMessage.h"
#include "../../../../include/Network/Client.h"
#include "../../../../include/Game/Card/Creature.h"

void CreatureAttackedEvent::sendMessage()
{
    CreatureAttackedMessage creatureAttackedMessage(*this);
    target->player->client->write(creatureAttackedMessage.getJSON());
}

CreatureAttackedEvent::CreatureAttackedEvent(const std::shared_ptr<Game> &game,
                                             const std::shared_ptr<Creature> &target,
                                             const std::shared_ptr<Creature> &attacker)
        : Event(game), target(target), attacker(attacker)
{
}

CreatureAttackedEvent::~CreatureAttackedEvent()
= default;
