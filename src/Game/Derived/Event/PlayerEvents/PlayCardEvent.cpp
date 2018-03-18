//
// Created by Sam on 3/18/2018.
//

#include "../../../../../include/Game/Derived/Event/PlayerEvents/PlayCardEvent.h"
#include "../../../../../include/Game/Core/Game.h"
#include "../../../../../include/Network/Derived/CardMovedMessage.h"
#include "../../../../../include/Game/Core/Card.h"
#include "../../../../../include/Game/Core/Container.h"
#include "../../../../../include/Game/Core/Player.h"
#include "../../../../../include/Game/Derived/Containers/CreatureZone.h"
#include "../../../../../include/Game/Derived/Containers/Hand.h"
#include "../../../../../include/Game/Derived/Containers/Deck.h"
#include "../../../../../include/Game/Derived/Containers/Graveyard.h"
#include "../../../../../include/Network/Client.h"

void PlayCardEvent::sendMessage()
{
    CardMovedMessage cardMovedMessage(card->player->hand, card->player->board->creatures, card);
    game->writePlayers(cardMovedMessage.getJSON());
}

PlayCardEvent::PlayCardEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Card>& card)
        : Event(game), card(card)
{
}

PlayCardEvent::~PlayCardEvent()
= default;
