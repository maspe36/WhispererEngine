//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_ACTION_H
#define WHISPERERENGINE_ACTION_H

#include <string>
#include <memory>

class Game;

/* A slice in time of an action to the current game state. */
class Event
{
public:
    virtual void sendMessage();

    std::shared_ptr<Game> game;

    explicit Event(const std::shared_ptr<Game>& game);
    virtual ~Event();
};


#endif //WHISPERERENGINE_ACTION_H
