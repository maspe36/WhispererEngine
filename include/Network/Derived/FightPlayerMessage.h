//
// Created by Sam on 3/19/2018.
//

#ifndef WHISPERERENGINE_FIGHTPLAYERMESSAGE_H
#define WHISPERERENGINE_FIGHTPLAYERMESSAGE_H


#include "../Message.h"

class FightPlayerMessage
        : public Message
{
public:
    std::string attackingPlayerTag;
    std::string cardTag;

    explicit FightPlayerMessage(const json &newJSON);
    ~FightPlayerMessage();
};


#endif //WHISPERERENGINE_FIGHTPLAYERMESSAGE_H
