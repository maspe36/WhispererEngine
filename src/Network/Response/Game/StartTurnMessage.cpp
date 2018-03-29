//
// Created by Sam on 3/17/2018.
//

#include "../../../../include/Network/Response/Game/StartTurnMessage.h"
#include "../../../../include/Game/Game.h"
#include "../../../../include/Game/Player.h"

StartTurnMessage::StartTurnMessage(StartTurnEvent startTurnEvent)
{
    auto game = startTurnEvent.game;
    auto toPlayer = startTurnEvent.player;

    std::vector<json> opponentsJSON = game->getOpponentJSON(toPlayer);

    rawJSON[TYPE_KEY] = Message::START_TURN;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
    addDataMember("gameState", game->getJSON(toPlayer));
}

StartTurnMessage::~StartTurnMessage()
= default;
