//
// Created by Sam on 3/30/2018.
//

#ifndef WHISPERERENGINE_ENDGAMEEVENT_H
#define WHISPERERENGINE_ENDGAMEEVENT_H


#include "../../Event.h"

class Game;
class Player;

class EndGameEvent
        : public Event
{
public:
    std::shared_ptr<Player> winner;

    void sendMessage() override;

    explicit EndGameEvent(const std::shared_ptr<Game>& game, const std::shared_ptr<Player>& winner);
    ~EndGameEvent();
};


#endif //WHISPERERENGINE_ENDGAMEEVENT_H
