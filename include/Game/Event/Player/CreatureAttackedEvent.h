//
// Created by Sam on 3/29/2018.
//

#ifndef WHISPERERENGINE_CREATUREATTACKEDEVENT_H
#define WHISPERERENGINE_CREATUREATTACKEDEVENT_H


#include "../../Event.h"

class Creature;
class Player;

class CreatureAttackedEvent
        : public Event
{
public:
    std::shared_ptr<Creature> target;
    std::shared_ptr<Creature> attacker;

    void sendMessage() override;

    explicit CreatureAttackedEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Creature>& target, const std::shared_ptr<Creature>& attacker);
    ~CreatureAttackedEvent();
};


#endif //WHISPERERENGINE_CREATUREATTACKEDEVENT_H
