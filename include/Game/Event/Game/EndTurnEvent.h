//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_ENDTURNEVENT_H
#define WHISPERERENGINE_ENDTURNEVENT_H

#include <memory>
#include "../../Event.h"

class Player;

class EndTurnEvent
        : public Event
{
public:
    std::shared_ptr<Player> player;

    void sendMessage() override;

    explicit EndTurnEvent(const std::shared_ptr<Game>& game);
    ~EndTurnEvent();
};

#endif //WHISPERERENGINE_ENDTURNEVENT_H
