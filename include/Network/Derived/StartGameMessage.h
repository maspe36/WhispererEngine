//
// Created by Sam on 3/7/2018.
//

#ifndef WHISPERERENGINE_STARTGAMEMESSAGE_H
#define WHISPERERENGINE_STARTGAMEMESSAGE_H


#include "../Message.h"

class Player;

class StartGameMessage
        : public Message
{
public:
    explicit StartGameMessage(std::shared_ptr<Player> toPlayer, std::vector<std::shared_ptr<Player>> players);
    virtual ~StartGameMessage();
};


#endif //WHISPERERENGINE_STARTGAMEMESSAGE_H
