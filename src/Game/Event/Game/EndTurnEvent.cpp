//
// Created by Sam on 3/18/2018.
//

#include "../../../../include/Game/Event/Game/EndTurnEvent.h"
#include "../../../../include/Game/Game.h"
#include "../../../../include/Network/Client.h"
#include "../../../../include/Network/Response/Game/EndTurnMessage.h"

void EndTurnEvent::sendMessage()
{
    EndTurnMessage endTurnMessage(game, player);
    player->client->write(endTurnMessage.getJSON());
}

EndTurnEvent::EndTurnEvent(const std::shared_ptr<Game>& game)
        : Event(game), player(game->activePlayer)
{
}

EndTurnEvent::~EndTurnEvent()
= default;
