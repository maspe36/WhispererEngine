//
// Created by Sam on 3/29/2018.
//

#include "../../../../include/Network/Request/Game/FightCreatureMessage.h"

FightCreatureMessage::FightCreatureMessage(const json &newJSON)
{
    loadJSON(newJSON);
    attackingPlayerTag = getDataMember("attackingPlayerTag");
    attackingCardTag = getDataMember("attackingCardTag");
    attackedCardTag = getDataMember("attackedCardTag");
}

FightCreatureMessage::~FightCreatureMessage()
= default;
