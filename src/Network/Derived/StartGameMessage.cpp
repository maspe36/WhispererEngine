//
// Created by Sam on 3/7/2018.
//

#include "../../../include/Network/Derived/StartGameMessage.h"
#include "../../../include/Network/Client.h"
#include "../../../include/Game/Core/Game.h"

StartGameMessage::StartGameMessage(std::shared_ptr<Player> toPlayer, std::shared_ptr<Game> game)
{
    std::vector<json> opponentsJSON = game->getOpponentJSON(toPlayer);

    for (const auto& player : game->players)
    {
        for (auto opponentJSON : opponentsJSON)
        {
            if (opponentJSON["playerID"] == player->tag)
            {
                opponentJSON["avatarURL"] = player->client->avatarURL;
            }
        }
    }

    rawJSON[TYPE_KEY] = Message::START_GAME;
    addDataMember("opponents", opponentsJSON);
    addDataMember("player", toPlayer->getState());
    addDataMember("activePlayerTag", game->activePlayer->tag);
}

StartGameMessage::~StartGameMessage()
= default;
