//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_DEADACTION_H
#define WHISPERERENGINE_DEADACTION_H


#include "../../../Core/Event.h"

/* A card being sent to the graveyard */
class DeadEvent : public Event
{
public:
    DeadEvent();
    ~DeadEvent();
};


#endif //WHISPERERENGINE_DEADACTION_H
