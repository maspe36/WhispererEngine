//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_AURAEFFECT_H
#define WHISPERERENGINE_AURAEFFECT_H


#include "../../Core/Effect.h"

/* An effect that is constantly emitting its ability */
class AuraEffect : public Effect
{
public:
    AuraEffect(func *effect);
    ~AuraEffect();
};


#endif //WHISPERERENGINE_AURAEFFECT_H
