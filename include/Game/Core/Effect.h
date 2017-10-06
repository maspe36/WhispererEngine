//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_EFFECT_H
#define WHISPERERENGINE_EFFECT_H

#include <functional>

/* Holds an effects trigger condition and actual effect implementation */
class Effect
{
public:
    std::function<void()> effect;

    Effect(std::function<void()> effect);
    ~Effect();
};


#endif //WHISPERERENGINE_EFFECT_H
