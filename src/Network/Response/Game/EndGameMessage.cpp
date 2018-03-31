//
// Created by Sam on 3/30/2018.
//

#include "../../../../include/Network/Response/Game/EndGameMessage.h"
#include "../../../../include/Game/Player.h"

EndGameMessage::EndGameMessage(EndGameEvent drawEvent)
{
    rawJSON[TYPE_KEY] = Message::END_GAME;
    rawJSON[DATA_KEY]["winningPlayerTag"] = drawEvent.winner->tag;
}

EndGameMessage::~EndGameMessage()
= default;
