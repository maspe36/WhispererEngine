//
// Created by Sam on 3/30/2018.
//

#ifndef WHISPERERENGINE_ENDGAMEMESSAGE_H
#define WHISPERERENGINE_ENDGAMEMESSAGE_H


#include "../../Message.h"
#include "../../../Game/Event/Game/EndGameEvent.h"

class Player;

class EndGameMessage
        : public Message
{
public:
    explicit EndGameMessage(EndGameEvent drawEvent);
    ~EndGameMessage();
};

#endif //WHISPERERENGINE_ENDGAMEMESSAGE_H
