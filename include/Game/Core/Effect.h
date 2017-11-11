//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_EFFECT_H
#define WHISPERERENGINE_EFFECT_H

/* A C++ function type */
typedef std::function<void()> func;

/* Holds an effects trigger condition and actual effect implementation */
class Effect
{
public:
    Effect();
    ~Effect();
};


#endif //WHISPERERENGINE_EFFECT_H
