//
// Created by Sam on 2/5/2018.
//

#include <utility>

#include "../../../include/Network/Derived/QueueMessage.h"

QueueMessage::QueueMessage(const json& newJSON)
{
    loadJSON(newJSON);
    deckID = getDataMember("id");
}

QueueMessage::~QueueMessage()
= default;
