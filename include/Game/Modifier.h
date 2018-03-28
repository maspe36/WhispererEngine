//
// Created by Sam on 9/25/2017.
//

#ifndef WHISPERERENGINE_AFFECT_H
#define WHISPERERENGINE_AFFECT_H


#include <memory>
#include "Utilities/Exportable.h"

class Modifier
        : public Exportable,
          public std::enable_shared_from_this<Modifier>
{
public:
    Modifier();
    ~Modifier();
};


#endif //WHISPERERENGINE_AFFECT_H
