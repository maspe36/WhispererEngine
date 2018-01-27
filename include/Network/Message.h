//
// Created by Sam on 1/15/2018.
//

#ifndef WHISPERERENGINE_MESSAGE_H
#define WHISPERERENGINE_MESSAGE_H

#include <string>
#include <include/rapidjson/document.h>

using namespace rapidjson;

class Message
{
public:
    std::string typeKey;
    std::string dataKey;

    std::string getJSON();
    std::string getMember(std::string key);
    std::string getDataMember(std::string key);
    void loadJSON(std::string json);
    void addMember(std::string key, std::string value);
    void addDataMember(std::string key, std::string value);

    explicit Message(std::string type);
    Message();
    virtual ~Message();

private:
    Document document;

    void initializeData();
    std::string getValue(bool isData, std::string key);
};


#endif //WHISPERERENGINE_MESSAGE_H
