//
// Created by Sam on 3/18/2018.
//

#ifndef WHISPERERENGINE_CONTAINER_H
#define WHISPERERENGINE_CONTAINER_H


#include "../Utilities/Exportable.h"

class Card;

class Container
    : public Exportable,
      public std::enable_shared_from_this<Container>
{
public:
    Container();
    virtual ~Container();
};


#endif //WHISPERERENGINE_CONTAINER_H
