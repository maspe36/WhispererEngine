//
// Created by Sam on 3/18/2018.
//

#include "../../../../include/Game/Event/Player/PlayCardEvent.h"
#include "../../../../include/Game/Game.h"
#include "../../../../include/Network/Response/Game/CardMovedMessage.h"
#include "../../../../include/Game/Card.h"
#include "../../../../include/Game/Container.h"
#include "../../../../include/Game/Player.h"
#include "../../../../include/Game/Container/Hand.h"
#include "../../../../include/Network/Client.h"

void PlayCardEvent::sendMessage()
{
    CardMovedMessage cardMovedMessage(*this);
    game->writePlayers(cardMovedMessage.getJSON());
}

PlayCardEvent::PlayCardEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Card>& card)
        : Event(game), card(card)
{
}

PlayCardEvent::~PlayCardEvent()
= default;
