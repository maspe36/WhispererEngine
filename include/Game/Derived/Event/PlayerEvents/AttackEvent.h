//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_ATTACKACTION_H
#define WHISPERERENGINE_ATTACKACTION_H


#include "../../../Core/Event.h"

/* A creature attack */
class AttackEvent : public Event
{
public:
    AttackEvent();
    ~AttackEvent();
};


#endif //WHISPERERENGINE_ATTACKACTION_H
