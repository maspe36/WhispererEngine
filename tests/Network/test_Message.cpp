//
// Created by Sam on 10/7/2017.
//

#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Network/Message.h"
#include "../../include/Network/Request/Lobby/AuthMessage.h"
#include <iostream>


TEST_CASE("Build JSON")
{
    std::string typeKey = "type";
    std::string typeValue = "Test";
    std::string dataKey = "data";
    std::string dataMemberKey = "name";
    std::string dataMemberValue = "Sam";

    // {"data":{"name":"Sam"},"type":"Test"}
    std::string json = "{\"" + dataKey + "\":{\"" + dataMemberKey + "\":\"" + dataMemberValue +
            "\"},\"" + typeKey + "\":\"" + typeValue +"\"}";

    Message message("Test");
    message.addDataMember("name", "Sam");
    std::string result = message.getJSON();
    std::string type = message.getMember("type");
    std::string name = message.getDataMember("name");

    REQUIRE(type == typeValue);
    REQUIRE(dataMemberValue == name);
    REQUIRE(result == json);
}

TEST_CASE("Parse JSON")
{
    std::string typeKey = "type";
    std::string typeValue = "Test";
    std::string dataKey = "data";
    std::string dataMemberKey = "name";
    std::string dataMemberValue = "Sam";

    // {"data":{"name":"Sam"},"type":"Test"}
    std::string json = "{\"" + dataKey + "\":{\"" + dataMemberKey + "\":\"" + dataMemberValue +
                       "\"},\"" + typeKey + "\":\"" + typeValue +"\"}";

    Message message;
    message.loadJSON(json);

    std::string result = message.getJSON();
    std::string type = message.getMember("type");
    std::string name = message.getDataMember("name");

    REQUIRE(type == typeValue);
    REQUIRE(name == dataMemberValue);
    REQUIRE(result == json);
}
