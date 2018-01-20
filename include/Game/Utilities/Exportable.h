//
// Created by Sam on 1/19/2018.
//

#ifndef WHISPERERENGINE_EXPORTABLE_H
#define WHISPERERENGINE_EXPORTABLE_H


#include <include/rapidjson/document.h>

using namespace rapidjson;

class Exportable
{
public:
    Document document;

    virtual void buildJSON();
    std::string exportJSON();
    Value getValue(std::string data);

    Exportable();
    virtual ~Exportable();
};


#endif //WHISPERERENGINE_EXPORTABLE_H
