//
// Created by Sam on 3/19/2018.
//

#ifndef WHISPERERENGINE_PLAYERATTACKEDMESSAGE_H
#define WHISPERERENGINE_PLAYERATTACKEDMESSAGE_H


#include "../../Message.h"

class Game;
class Card;

class PlayerAttackedMessage
        : public Message
{
public:
    explicit PlayerAttackedMessage(std::shared_ptr<Game> game, std::shared_ptr<Card> card);
    ~PlayerAttackedMessage();
};


#endif //WHISPERERENGINE_PLAYERATTACKEDMESSAGE_H
