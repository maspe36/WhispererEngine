//
// Created by Sam on 3/10/2018.
//

#include "../../../../include/Game/Event/Game/StartGameEvent.h"
#include "../../../../include/Game/Game.h"
#include "../../../../include/Network/Client.h"

void StartGameEvent::sendMessage()
{
    for (const auto& player : game->players)
    {
        StartGameMessage startGameMessage(player, game);
        player->client->write(startGameMessage.getJSON());
    }
}

StartGameEvent::StartGameEvent(const std::shared_ptr<Game>& game)
        : Event(game)
{
}

StartGameEvent::~StartGameEvent()
= default;
