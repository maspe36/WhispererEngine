//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CARDMOVEDMESSAGE_H
#define WHISPERERENGINE_CARDMOVEDMESSAGE_H


#include "../../Message.h"
#include "../../../Game/Event/Player/PlayCardEvent.h"
#include "../../../Game/Event/Game/CreatureDestroyedEvent.h"

class Container;

class CardMovedMessage
        : public Message
{
public:
    explicit CardMovedMessage(PlayCardEvent playCardEvent);
    explicit CardMovedMessage(CreatureDestroyedEvent creatureDestroyedEvent);
    ~CardMovedMessage();

private:
    int getZoneID(const std::shared_ptr<Container>& container);
};


#endif //WHISPERERENGINE_CARDMOVEDMESSAGE_H
