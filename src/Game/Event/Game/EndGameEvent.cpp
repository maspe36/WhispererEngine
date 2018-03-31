//
// Created by Sam on 3/30/2018.
//

#include "../../../../include/Game/Event/Game/EndGameEvent.h"
#include "../../../../include/Network/Response/Game/EndGameMessage.h"
#include "../../../../include/Game/Game.h"

void EndGameEvent::sendMessage()
{
    EndGameMessage endGameMessage(*this);
    game->writePlayers(endGameMessage.getJSON());
}

EndGameEvent::EndGameEvent(const std::shared_ptr<Game> &game, const std::shared_ptr<Player> &winner)
        : Event(game), winner(winner)
{
}

EndGameEvent::~EndGameEvent()
= default;
