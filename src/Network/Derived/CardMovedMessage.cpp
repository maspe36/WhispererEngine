//
// Created by Sam on 3/18/2018.
//

#include "../../../include/Network/Derived/CardMovedMessage.h"
#include "../../../include/Game/Core/Card.h"
#include "../../../include/Game/Core/Container.h"
#include "../../../include/Game/Core/Player.h"
#include "../../../include/Game/Derived/Containers/CreatureZone.h"
#include "../../../include/Game/Derived/Containers/Deck.h"
#include "../../../include/Game/Derived/Containers/Graveyard.h"
#include "../../../include/Game/Derived/Containers/Hand.h"

CardMovedMessage::CardMovedMessage(const std::shared_ptr<Container> &origin,
                                   const std::shared_ptr<Container> &destination,
                                   const std::shared_ptr<Card> &card)
{
    rawJSON[TYPE_KEY] = Message::CARD_MOVED;
    addDataMember("originZoneID", getZoneID(origin));
    addDataMember("destinationZoneID", getZoneID(destination));
    addDataMember("card", card->getJSON());
    addDataMember("playerTag", card->player->tag);
}

CardMovedMessage::~CardMovedMessage()
= default;

int CardMovedMessage::getZoneID(const std::shared_ptr<Container>& container)
{
    if (std::dynamic_pointer_cast<Deck>(container))
    {
        return 0;
    }
    else if (std::dynamic_pointer_cast<Hand>(container))
    {
        return 1;
    }
    else if (std::dynamic_pointer_cast<CreatureZone>(container))
    {
        return 2;
    }
    else if (std::dynamic_pointer_cast<Graveyard>(container))
    {
        return 3;
    }

    throw std::runtime_error("Attempted to move a card into an unknown container");
}
