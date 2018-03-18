//
// Created by Sam on 3/10/2018.
//

#include "../../../../../include/Game/Derived/Event/GameEvents/StartGameEvent.h"

StartGameEvent::StartGameEvent(std::shared_ptr<Game> game)
        : game(game)
{
}

StartGameEvent::~StartGameEvent()
= default;
