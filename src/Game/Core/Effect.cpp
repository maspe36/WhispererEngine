//
// Created by Sam on 9/29/2017.
//

#include "../../../include/Game/Core/Effect.h"

bool Effect::triggered(const std::shared_ptr<Event>& event)
{
    return false;
}

Effect::Effect()
= default;

Effect::~Effect()
= default;
