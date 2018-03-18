//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_STARTTURNEVENT_H
#define WHISPERERENGINE_STARTTURNEVENT_H

#include "../../../Core/Event.h"

class Player;

class StartTurnEvent
        : public Event
{
public:
    std::shared_ptr<Player> player;

    void sendMessage() override;

    explicit StartTurnEvent(const std::shared_ptr<Game>& game);
    ~StartTurnEvent();
};


#endif //WHISPERERENGINE_STARTTURNEVENT_H
