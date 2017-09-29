//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_DRAWACTION_H
#define WHISPERERENGINE_DRAWACTION_H


#include "../../../Core/Event.h"

/* A player drawing card(s) */
class DrawEvent : public Event
{
public:
    DrawEvent();
    ~DrawEvent();
};


#endif //WHISPERERENGINE_DRAWACTION_H
