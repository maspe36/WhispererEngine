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
    static const std::string AUTH;
    static const std::string QUEUE;

    std::string typeKey;
    std::string dataKey;

    std::string getType();
    std::string getJSON();
    std::string getMember(std::string key);
    std::string getDataMember(std::string key);
    void loadJSON(std::string json);
    void addMember(std::string key, std::string value);
    void addDataMember(std::string key, std::string value);

    static const std::string success();
    static const std::string fail();
    static const std::string fail(std::string cause);
    static const std::string auth();

    explicit Message(std::string type);
    Message();
    virtual ~Message();

private:
    Document document;

    void initializeData();
    std::string getValue(bool isData, std::string key);
};


#endif //WHISPERERENGINE_MESSAGE_H
