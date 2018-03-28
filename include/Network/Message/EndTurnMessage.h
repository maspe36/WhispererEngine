//
// Created by Sam on 3/17/2018.
//

#ifndef WHISPERERENGINE_ENDTURNMESSAGE_H
#define WHISPERERENGINE_ENDTURNMESSAGE_H


#include "../Message.h"

class Game;
class Player;

class EndTurnMessage
        : public Message
{
public:
    explicit EndTurnMessage(std::shared_ptr<Game> game, std::shared_ptr<Player> toPlayer);
    ~EndTurnMessage() override;
};


#endif //WHISPERERENGINE_ENDTURNMESSAGE_H
