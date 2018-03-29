//
// Created by Sam on 3/17/2018.
//

#ifndef WHISPERERENGINE_ENDTURNMESSAGE_H
#define WHISPERERENGINE_ENDTURNMESSAGE_H


#include "../../Message.h"
#include "../../../Game/Event/Game/EndTurnEvent.h"


class EndTurnMessage
        : public Message
{
public:
    explicit EndTurnMessage(EndTurnEvent endTurnEvent);
    ~EndTurnMessage() override;
};


#endif //WHISPERERENGINE_ENDTURNMESSAGE_H
