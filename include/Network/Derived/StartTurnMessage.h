//
// Created by Sam on 3/17/2018.
//

#ifndef WHISPERERENGINE_STARTTURNMESSAGE_H
#define WHISPERERENGINE_STARTTURNMESSAGE_H


#include "../Message.h"

class Game;
class Player;

class StartTurnMessage
    : public Message
{
public:
    explicit StartTurnMessage(std::shared_ptr<Game> game, std::shared_ptr<Player> toPlayer);
    ~StartTurnMessage() override;
};


#endif //WHISPERERENGINE_STARTTURNMESSAGE_H
