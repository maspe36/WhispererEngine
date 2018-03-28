//
// Created by Sam on 3/19/2018.
//

#include "../../../include/Network/Message/FightPlayerMessage.h"

FightPlayerMessage::FightPlayerMessage(const json &newJSON)
{
    loadJSON(newJSON);
    attackingPlayerTag = getDataMember("attackingPlayerTag");
    cardTag = getDataMember("cardTag");
}

FightPlayerMessage::~FightPlayerMessage()
= default;
