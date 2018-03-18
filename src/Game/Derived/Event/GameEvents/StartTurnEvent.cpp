//
// Created by Sam on 3/18/2018.
//

#include "../../../../../include/Game/Derived/Event/GameEvents/StartTurnEvent.h"
#include "../../../../../include/Game/Core/Game.h"
#include "../../../../../include/Network/Client.h"
#include "../../../../../include/Network/Derived/StartTurnMessage.h"

void StartTurnEvent::sendMessage()
{
    StartTurnMessage startTurnMessage(game, player);
    player->client->write(startTurnMessage.getJSON());
}

StartTurnEvent::StartTurnEvent(const std::shared_ptr<Game>& game)
        : Event(game), player(game->activePlayer)
{
}

StartTurnEvent::~StartTurnEvent()
= default;
