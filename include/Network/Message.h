//
// Created by Sam on 1/15/2018.
//

#ifndef WHISPERERENGINE_MESSAGE_H
#define WHISPERERENGINE_MESSAGE_H

#include <string>
#include "../Game/Utilities/Exportable.h"


class Message: public Exportable
{
public:
    std::string type;
    std::string data;

    void buildJSON();
    std::string getJSON();

    Message(std::string type, std::string data);
    Message();
    ~Message();
};


#endif //WHISPERERENGINE_MESSAGE_H
