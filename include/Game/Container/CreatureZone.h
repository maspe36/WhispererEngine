//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CREATUREZONE_H
#define WHISPERERENGINE_CREATUREZONE_H


#include "../Container.h"

class CreatureZone
        : public Container
{
public:
    int sizeLimit = 6;

    void addCard(const std::shared_ptr<Card>& card) override;

    CreatureZone();
    ~CreatureZone();
};


#endif //WHISPERERENGINE_CREATUREZONE_H
