//
// Created by Sam on 1/15/2018.
//

#ifndef WHISPERERENGINE_MESSAGE_H
#define WHISPERERENGINE_MESSAGE_H

#include <string>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Message
{
public:
    static std::string AUTH;
    static std::string QUEUE;
    static std::string TYPE_KEY;
    static std::string DATA_KEY;

    std::string getJSON();
    void loadJSON(std::string json);
    void addDataMember(std::string key, std::string value);

    std::string getType();
    std::string getMember(std::string key);
    std::string getDataMember(std::string key);

    static const std::string success();
    static const std::string fail();
    static const std::string fail(std::string cause);
    static const std::string auth();

    explicit Message(std::string type);
    Message();
    virtual ~Message();

private:
    json rawJSON;
};


#endif //WHISPERERENGINE_MESSAGE_H
