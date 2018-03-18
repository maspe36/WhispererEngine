//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_GRAVEYARD_H
#define WHISPERERENGINE_GRAVEYARD_H


#include "../../Core/Container.h"

class Graveyard
        : public Container
{
public:
    std::vector<std::shared_ptr<Card>> cards;

    Graveyard();
    ~Graveyard();
};


#endif //WHISPERERENGINE_GRAVEYARD_H
