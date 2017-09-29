//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_PLAYACTION_H
#define WHISPERERENGINE_PLAYACTION_H


#include "../../../Core/Event.h"

/* A card entering play */
class PlayEvent : public Event
{
public:
    PlayEvent();
    ~PlayEvent();
};


#endif //WHISPERERENGINE_PLAYACTION_H
