//
// Created by Sam on 3/7/2018.
//

#include "../../../include/Network/Derived/StartGameMessage.h"
#include "../../../include/Network/Client.h"

StartGameMessage::StartGameMessage(std::shared_ptr<Player> toPlayer, std::vector<std::shared_ptr<Player>> players)
{
    std::vector<json> opponentsJSON;
    for (const auto& player : players)
    {
        if (player != toPlayer)
        {
            auto opponentJSON = player->getOpponentState();
            opponentJSON["avatarURL"] = player->client->avatarURL;
            opponentsJSON.push_back(opponentJSON);
        }
    }

    rawJSON[TYPE_KEY] = Message::START_GAME;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
}

StartGameMessage::~StartGameMessage()
= default;
