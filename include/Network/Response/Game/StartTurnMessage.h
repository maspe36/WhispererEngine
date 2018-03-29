//
// Created by Sam on 3/17/2018.
//

#ifndef WHISPERERENGINE_STARTTURNMESSAGE_H
#define WHISPERERENGINE_STARTTURNMESSAGE_H


#include "../../Message.h"
#include "../../../Game/Event/Game/StartTurnEvent.h"

class Game;
class Player;

class StartTurnMessage
    : public Message
{
public:
    explicit StartTurnMessage(StartTurnEvent startTurnEvent);
    ~StartTurnMessage() override;
};


#endif //WHISPERERENGINE_STARTTURNMESSAGE_H
