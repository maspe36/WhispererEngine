//
// Created by Sam on 2/5/2018.
//

#include "../../../../include/Network/Request/Lobby/QueueMessage.h"

QueueMessage::QueueMessage(const json& newJSON)
{
    loadJSON(newJSON);
    deckID = getDataMember("deckID");
}

QueueMessage::~QueueMessage()
= default;
