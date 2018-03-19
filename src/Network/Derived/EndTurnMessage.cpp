//
// Created by Sam on 3/17/2018.
//

#include "../../../include/Network/Derived/EndTurnMessage.h"
#include "../../../include/Game/Core/Game.h"
#include "../../../include/Game/Core/Player.h"

EndTurnMessage::EndTurnMessage(std::shared_ptr<Game> game, std::shared_ptr<Player> toPlayer)
{
    std::vector<json> opponentsJSON = game->getOpponentJSON(toPlayer);

    rawJSON[TYPE_KEY] = Message::END_TURN;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
    addDataMember("gameState", game->getJSON(toPlayer));
}

EndTurnMessage::~EndTurnMessage()
= default;
