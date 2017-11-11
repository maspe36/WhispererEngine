//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_AURAEFFECT_H
#define WHISPERERENGINE_AURAEFFECT_H


#include "../../Core/Effect.h"
#include <vector>

class Modifier;

/* An effect that is constantly emitting its ability */
class AuraEffect : public Effect
{
public:
    std::vector<Modifier*> modifiers;

    bool isApplied();

    AuraEffect(std::vector<Modifier*> modifiers, func *isApplied);
    ~AuraEffect();
};


#endif //WHISPERERENGINE_AURAEFFECT_H
