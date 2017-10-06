//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_TRIGGEREFFECT_H
#define WHISPERERENGINE_TRIGGEREFFECT_H


#include "../../Core/Effect.h"

/* An effect that has a condition to be met for it to trigger */
class TriggerEffect : public Effect
{
public:
    std::function<void()> isEffectTriggered;

    TriggerEffect(std::function<void()> effect, std::function<void()> isEffectTriggered);
    ~TriggerEffect();
};


#endif //WHISPERERENGINE_TRIGGEREFFECT_H
