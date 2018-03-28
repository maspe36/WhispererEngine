//
// Created by Sam on 9/25/2017.
//

#include "../../include/Game/Event.h"

Event::Event(const std::shared_ptr<Game>& game)
        : game(game)
{
}

Event::~Event()
= default;

void Event::sendMessage()
{
}
