//
// Created by Sam on 3/28/2018.
//

#ifndef WHISPERERENGINE_DRAWCARDMESSAGE_H
#define WHISPERERENGINE_DRAWCARDMESSAGE_H

#include "../../Message.h"
#include "../../../Game/Event/Player/DrawEvent.h"

class Card;

class DrawMessage
        : public Message
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    void toOpponent();
    void toSelf();

    explicit DrawMessage(DrawEvent drawEvent);
    ~DrawMessage();
};


#endif //WHISPERERENGINE_DRAWCARDMESSAGE_H
