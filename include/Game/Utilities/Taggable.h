//
// Created by Sam on 1/3/2018.
//

#ifndef WHISPERERENGINE_EXPORTABLE_H
#define WHISPERERENGINE_EXPORTABLE_H


#include <string>


class Taggable
{
public:
    const std::string tag;

    Taggable();
    virtual ~Taggable();
};


#endif //WHISPERERENGINE_EXPORTABLE_H
