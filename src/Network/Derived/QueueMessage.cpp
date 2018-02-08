//
// Created by Sam on 2/5/2018.
//

#include <utility>

#include "../../../include/Network/Derived/QueueMessage.h"

QueueMessage::QueueMessage(std::string json) : Message()
{
    loadJSON(std::move(json));
    deckID = getDataMember("deckID");
}

QueueMessage::~QueueMessage()
= default;
