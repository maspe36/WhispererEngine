//
// Created by Sam on 3/10/2018.
//

#ifndef WHISPERERENGINE_MOVECARDMESSAGE_H
#define WHISPERERENGINE_MOVECARDMESSAGE_H


#include "../../Message.h"

class PlayCardMessage
        : public Message
{
public:
    std::string cardTag;

    explicit PlayCardMessage(const json &newJSON);
    ~PlayCardMessage();
};


#endif //WHISPERERENGINE_MOVECARDMESSAGE_H
