//
// Created by Sam on 3/28/2018.
//

#ifndef WHISPERERENGINE_DRAWCARDMESSAGE_H
#define WHISPERERENGINE_DRAWCARDMESSAGE_H

#include "../Message.h"

class Card;
class Player;
class Game;

class DrawMessage
        : public Message
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    void toOpponent();
    void toSelf();

    explicit DrawMessage(std::shared_ptr<Game> game, std::vector<std::shared_ptr<Card>> cards, std::shared_ptr<Player> toPlayer);
    ~DrawMessage();
};


#endif //WHISPERERENGINE_DRAWCARDMESSAGE_H
