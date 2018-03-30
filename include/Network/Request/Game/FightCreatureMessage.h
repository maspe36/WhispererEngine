//
// Created by Sam on 3/29/2018.
//

#ifndef WHISPERERENGINE_FIGHTCREATUREMESSAGE_H
#define WHISPERERENGINE_FIGHTCREATUREMESSAGE_H


#include "../../Message.h"

class Creature;
class Player;

class FightCreatureMessage
        : public Message
{
public:
    std::string attackingPlayerTag;
    std::string attackingCardTag;
    std::string attackedCardTag;

    explicit FightCreatureMessage(const json& newJSON);
    ~FightCreatureMessage() override;
};


#endif //WHISPERERENGINE_FIGHTCREATUREMESSAGE_H
