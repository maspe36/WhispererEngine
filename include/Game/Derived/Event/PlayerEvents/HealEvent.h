//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_HEALEVENT_H
#define WHISPERERENGINE_HEALEVENT_H


#include "../../../Core/Event.h"

/* A player or card being healed */
class HealEvent : public Event
{
public:
    HealEvent();
    ~HealEvent();
};


#endif //WHISPERERENGINE_HEALEVENT_H
