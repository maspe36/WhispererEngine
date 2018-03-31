//
// Created by Sam on 3/30/2018.
//

#ifndef WHISPERERENGINE_CREATUREDESTROYEDEVENT_H
#define WHISPERERENGINE_CREATUREDESTROYEDEVENT_H


#include "../../Event.h"

class Game;
class Creature;

class CreatureDestroyedEvent
        : public Event
{
public:
    std::shared_ptr<Creature> creature;

    explicit CreatureDestroyedEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Creature>& creature);
    ~CreatureDestroyedEvent();
};


#endif //WHISPERERENGINE_CREATUREDESTROYEDEVENT_H
