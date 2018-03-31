//
// Created by Sam on 3/29/2018.
//

#include "../../../../include/Network/Response/Game/CreatureAttackedMessage.h"
#include "../../../../include/Game/Player.h"
#include "../../../../include/Game/Card/Creature.h"

CreatureAttackedMessage::CreatureAttackedMessage(CreatureAttackedEvent creatureAttackedEvent)
{
    auto target = creatureAttackedEvent.target;
    auto attacker = creatureAttackedEvent.attacker;

    rawJSON[TYPE_KEY] = Message::CREATURE_ATTACKED;
    rawJSON[DATA_KEY]["targetCardTag"] = target->tag;
    rawJSON[DATA_KEY]["attackerCardTag"] = attacker->tag;
    rawJSON[DATA_KEY]["attackerOwnerTag"] = creatureAttackedEvent.attacker->player->tag;
}

CreatureAttackedMessage::~CreatureAttackedMessage()
= default;
