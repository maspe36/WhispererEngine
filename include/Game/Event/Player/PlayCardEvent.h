//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_PLAYCARDEVENT_H
#define WHISPERERENGINE_PLAYCARDEVENT_H


#include "../../Event.h"

class Card;

class PlayCardEvent
        : public Event
{
public:
    std::shared_ptr<Card> card;

    void sendMessage() override;

    explicit PlayCardEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Card>& card);
    ~PlayCardEvent();
};


#endif //WHISPERERENGINE_PLAYCARDEVENT_H
