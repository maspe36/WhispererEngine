//
// Created by Sam on 9/29/2017.
//

#ifndef WHISPERERENGINE_EFFECT_H
#define WHISPERERENGINE_EFFECT_H

#include <functional>
#include <memory>
#include "../Utilities/Exportable.h"
#include "Event.h"

/* Holds an effects trigger condition and actual effect implementation */
class Effect
        : public Exportable,
          public std::enable_shared_from_this<Effect>
{
public:
    bool triggered(const std::shared_ptr<Event>& event);

    Effect();
    ~Effect();
};


#endif //WHISPERERENGINE_EFFECT_H
