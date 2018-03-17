//
// Created by Sam on 3/17/2018.
//

#include "../../../include/Network/Derived/EndTurnMessage.h"

EndTurnMessage::EndTurnMessage()
{
    rawJSON[TYPE_KEY] = Message::END_TURN;
}

EndTurnMessage::~EndTurnMessage()
= default;
