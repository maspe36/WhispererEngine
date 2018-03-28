//
// Created by Sam on 3/10/2018.
//

#include "../../../include/Network/Message/PlayCardMessage.h"

PlayCardMessage::PlayCardMessage(const json &newJSON)
{
    loadJSON(newJSON);
    cardTag = getDataMember("cardTag");
}

PlayCardMessage::~PlayCardMessage()
= default;
