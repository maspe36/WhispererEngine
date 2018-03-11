//
// Created by Sam on 3/10/2018.
//

#include "../../../include/Network/Derived/PlayCardMessage.h"

PlayCardMessage::PlayCardMessage(const json &newJSON)
{
    loadJSON(newJSON);
    cardTag = getDataMember("cardTag");
}

PlayCardMessage::~PlayCardMessage()
= default;
