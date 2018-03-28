//
// Created by Sam on 2/5/2018.
//

#ifndef WHISPERERENGINE_QUEUEMESSAGE_H
#define WHISPERERENGINE_QUEUEMESSAGE_H


#include "../Message.h"

class QueueMessage
        : public Message
{
public:
    std::string deckID;

    explicit QueueMessage(const json& newJSON);
    ~QueueMessage() override;
};



#endif //WHISPERERENGINE_QUEUEMESSAGE_H
