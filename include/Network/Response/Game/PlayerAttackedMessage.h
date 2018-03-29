//
// Created by Sam on 3/19/2018.
//

#ifndef WHISPERERENGINE_PLAYERATTACKEDMESSAGE_H
#define WHISPERERENGINE_PLAYERATTACKEDMESSAGE_H


#include "../../Message.h"
#include "../../../Game/Event/Player/PlayerAttackedEvent.h"

class Game;
class Card;

class PlayerAttackedMessage
        : public Message
{
public:
    explicit PlayerAttackedMessage(PlayerAttackedEvent playerAttackedEvent);
    ~PlayerAttackedMessage();
};


#endif //WHISPERERENGINE_PLAYERATTACKEDMESSAGE_H
