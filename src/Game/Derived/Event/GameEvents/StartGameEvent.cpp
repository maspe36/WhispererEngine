//
// Created by Sam on 3/10/2018.
//

#include "../../../../../include/Game/Derived/Event/GameEvents/StartGameEvent.h"
#include "../../../../../include/Game/Core/Game.h"
#include "../../../../../include/Network/Client.h"

StartGameEvent::StartGameEvent(const std::shared_ptr<Game>& game)
        : Event(game)
{
}

void StartGameEvent::sendMessage()
{
    for (const auto& player : game->players)
    {
        StartGameMessage startGameMessage(player, game);
        player->client->write(startGameMessage.getJSON());
    }
}

StartGameEvent::~StartGameEvent()
= default;
