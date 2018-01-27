//
// Created by Sam on 1/27/2018.
//

#include "AuthMessage.h"

#include <utility>

AuthMessage::AuthMessage(std::string json) : Message()
{
    loadJSON(std::move(json));
    name = getDataMember("name");
    clientID = getDataMember("clientID");
}

AuthMessage::~AuthMessage()
= default;


