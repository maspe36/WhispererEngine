//
// Created by Sam on 3/17/2018.
//

#ifndef WHISPERERENGINE_ENDTURNMESSAGE_H
#define WHISPERERENGINE_ENDTURNMESSAGE_H


#include "../Message.h"

class EndTurnMessage
        : public Message
{
public:
    explicit EndTurnMessage();
    ~EndTurnMessage() override;
};


#endif //WHISPERERENGINE_ENDTURNMESSAGE_H
