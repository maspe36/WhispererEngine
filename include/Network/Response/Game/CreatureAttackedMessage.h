//
// Created by Sam on 3/29/2018.
//

#ifndef WHISPERERENGINE_CREATUREATTACKEDMESSAGE_H
#define WHISPERERENGINE_CREATUREATTACKEDMESSAGE_H


#include "../../Message.h"
#include "../../../Game/Event/Player/CreatureAttackedEvent.h"

class CreatureAttackedMessage
        : public Message
{
public:
    explicit CreatureAttackedMessage(CreatureAttackedEvent creatureAttackedEvent);
    ~CreatureAttackedMessage();
};



#endif //WHISPERERENGINE_CREATUREATTACKEDMESSAGE_H
