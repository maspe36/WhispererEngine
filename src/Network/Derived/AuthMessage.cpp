//
// Created by Sam on 1/27/2018.
//

#include "../../../include/Network/Derived/AuthMessage.h"

#include <utility>

AuthMessage::AuthMessage(std::string json) : Message()
{
    loadJSON(std::move(json));
    token = getDataMember("token");
}

AuthMessage::~AuthMessage()
= default;


