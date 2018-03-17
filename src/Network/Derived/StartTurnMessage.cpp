//
// Created by Sam on 3/17/2018.
//

#include "../../../include/Network/Derived/StartTurnMessage.h"
#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Player.h"

StartTurnMessage::StartTurnMessage(std::shared_ptr<Game> game, std::shared_ptr<Player> toPlayer)
{
    std::vector<json> opponentsJSON = game->getOpponentJSON(toPlayer);

    rawJSON[TYPE_KEY] = Message::START_TURN;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
}

StartTurnMessage::~StartTurnMessage()
= default;
