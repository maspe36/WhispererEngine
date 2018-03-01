//
// Created by Sam on 3/1/2018.
//

#ifndef WHISPERERENGINE_EXPORTABLE_H
#define WHISPERERENGINE_EXPORTABLE_H


#include <nlohmann/json.hpp>
#include "Taggable.h"

using json = nlohmann::json;

class Exportable
        : public Taggable
{
public:
    virtual json getJSON();

    Exportable();
    virtual ~Exportable();
};


#endif //WHISPERERENGINE_EXPORTABLE_H
