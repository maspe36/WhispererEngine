//
// Created by Sam on 3/19/2018.
//

#include "../../../include/Network/Derived/FightPlayerMessage.h"

FightPlayerMessage::FightPlayerMessage(const json &newJSON)
{
    loadJSON(newJSON);
    attackingPlayerTag = getDataMember("attackingPlayerTag");
    cardTag = getDataMember("cardTag");
}

FightPlayerMessage::~FightPlayerMessage()
= default;
