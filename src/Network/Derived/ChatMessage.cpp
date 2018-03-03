//
// Created by Sam on 3/3/2018.
//

#include "../../../include/Network/Derived/ChatMessage.h"

ChatMessage::ChatMessage(const json &newJSON)
{
    loadJSON(newJSON);
    text = getDataMember("text");
}

ChatMessage::~ChatMessage()
= default;
