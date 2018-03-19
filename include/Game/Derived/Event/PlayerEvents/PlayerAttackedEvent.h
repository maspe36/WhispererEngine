//
// Created by Sam on 3/19/2018.
//

#ifndef WHISPERERENGINE_PLAYERATTACKEDEVENT_H
#define WHISPERERENGINE_PLAYERATTACKEDEVENT_H


#include "../../../Core/Event.h"

class Card;
class Player;

class PlayerAttackedEvent
        : public Event
{
public:
    std::shared_ptr<Card> card;
    std::shared_ptr<Player> targetPlayer;

    void sendMessage() override;

    explicit PlayerAttackedEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Card>& card, const std::shared_ptr<Player>& targetPlayer);
    ~PlayerAttackedEvent();
};


#endif //WHISPERERENGINE_PLAYERATTACKEDEVENT_H
