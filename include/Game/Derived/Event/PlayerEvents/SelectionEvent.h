//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_PLAYERSELECTIONEVENT_H
#define WHISPERERENGINE_PLAYERSELECTIONEVENT_H


#include "../../../Core/Event.h"

/* A player or card being selected */
class SelectionEvent : public Event
{
public:
    SelectionEvent();
    ~SelectionEvent();
};


#endif //WHISPERERENGINE_PLAYERSELECTIONEVENT_H
