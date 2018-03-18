//
// Created by Sam on 3/18/2018.
//

#include "../../../../../include/Game/Derived/Event/GameEvents/EndTurnEvent.h"
#include "../../../../../include/Game/Core/Game.h"
#include "../../../../../include/Network/Client.h"
#include "../../../../../include/Network/Derived/EndTurnMessage.h"

void EndTurnEvent::sendMessage()
{
    EndTurnMessage endTurnMessage;
    player->client->write(endTurnMessage.getJSON());
}

EndTurnEvent::EndTurnEvent(const std::shared_ptr<Game>& game)
        : Event(game), player(game->activePlayer)
{
}

EndTurnEvent::~EndTurnEvent()
= default;
