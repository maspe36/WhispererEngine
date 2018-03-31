//
// Created by Sam on 3/7/2018.
//

#include "../../../../include/Network/Response/Game/StartGameMessage.h"
#include "../../../../include/Network/Client.h"
#include "../../../../include/Game/Game.h"

StartGameMessage::StartGameMessage(std::shared_ptr<Player> toPlayer, std::shared_ptr<Game> game)
{
    std::vector<json> opponentsJSON = game->getOpponentJSON(toPlayer);

    rawJSON[TYPE_KEY] = Message::START_GAME;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
    addDataMember("activePlayerTag", game->activePlayer->tag);
}

StartGameMessage::~StartGameMessage()
= default;
