//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CREATUREZONE_H
#define WHISPERERENGINE_CREATUREZONE_H


#include "../../Core/Container.h"

class Creature;

class CreatureZone
        : public Container
{
public:
    std::vector<std::shared_ptr<Creature>> cards;

    json getJSON() override;

    CreatureZone();
    ~CreatureZone();
};


#endif //WHISPERERENGINE_CREATUREZONE_H
