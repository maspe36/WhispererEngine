//
// Created by Sam on 3/7/2018.
//

#include "../../../include/Network/Derived/StartGameMessage.h"
#include "../../../include/Game/Core/Player.h"

StartGameMessage::StartGameMessage(std::shared_ptr<Player> toPlayer, std::vector<std::shared_ptr<Player>> players)
{
    std::vector<json> opponentsJSON;
    for (const auto& player : players)
    {
        if (player != toPlayer)
        {
            opponentsJSON.push_back(player->getOpponentJSON());
        }
    }

    rawJSON[TYPE_KEY] = Message::START_GAME;
    addDataMember("playerID", toPlayer->tag);
    addDataMember("opponents", opponentsJSON);
    addDataMember("hand", toPlayer->hand->getJSON());
}

StartGameMessage::~StartGameMessage()
= default;
