//
// Created by Sam on 1/27/2018.
//

#include "../../../include/Network/Derived/AuthMessage.h"

AuthMessage::AuthMessage(const json& newJSON)
{
    loadJSON(newJSON);
    token = getDataMember("token");
}

AuthMessage::~AuthMessage()
= default;
