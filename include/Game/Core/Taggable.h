//
// Created by Sam on 1/3/2018.
//

#ifndef WHISPERERENGINE_TAGGABLE_H
#define WHISPERERENGINE_TAGGABLE_H


#include <string>


class Taggable
{
public:
    Taggable();
    virtual ~Taggable();
    const std::string tag;
};


#endif //WHISPERERENGINE_TAGGABLE_H
