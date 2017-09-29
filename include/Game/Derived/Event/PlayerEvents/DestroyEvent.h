//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_DESTROYEVENT_H
#define WHISPERERENGINE_DESTROYEVENT_H


#include "../../../Core/Event.h"

/* A card being destroyed */
class DestroyEvent : public Event
{
public:
    DestroyEvent();
    ~DestroyEvent();
};


#endif //WHISPERERENGINE_DESTROYEVENT_H
