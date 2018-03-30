//
// Created by Sam on 3/30/2018.
//

#include "../../../../include/Game/Event/Game/CreatureDestroyedEvent.h"
#include "../../../../include/Network/Response/Game/CardMovedMessage.h"
#include "../../../../include/Game/Game.h"

void CreatureDestroyedEvent::sendMessage()
{
    CardMovedMessage cardMovedMessage(*this);
    game->writePlayers(cardMovedMessage.getJSON());
}

CreatureDestroyedEvent::CreatureDestroyedEvent(const std::shared_ptr<Game> &game,
                                               const std::shared_ptr<Creature> &creature)
        : Event(game), creature(creature)
{
}

CreatureDestroyedEvent::~CreatureDestroyedEvent()
= default;
