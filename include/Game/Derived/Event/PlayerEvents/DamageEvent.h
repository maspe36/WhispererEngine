//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_DAMAGEEVENT_H
#define WHISPERERENGINE_DAMAGEEVENT_H


#include "../../../Core/Event.h"

/* A creature or player taking damage */
class DamageEvent : public Event
{
public:
    DamageEvent();
    ~DamageEvent();
};


#endif //WHISPERERENGINE_DAMAGEEVENT_H
