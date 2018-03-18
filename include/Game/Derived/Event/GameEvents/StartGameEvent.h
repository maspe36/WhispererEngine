//
// Created by Sam on 3/10/2018.
//

#ifndef WHISPERERENGINE_STARTEVENT_H
#define WHISPERERENGINE_STARTEVENT_H


#include "../../../Core/Event.h"
#include "../../../../Network/Derived/StartGameMessage.h"

class Game;

class StartGameEvent
        : public Event
{
public:
    void sendMessage() override;

    explicit StartGameEvent(const std::shared_ptr<Game>& game);
    ~StartGameEvent();
};


#endif //WHISPERERENGINE_STARTEVENT_H
