//
// Created by Sam on 10/7/2017.
//

#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Network/Message.h"
#include "../../include/Network/Derived/AuthMessage.h"
#include <iostream>


TEST_CASE("Build JSON")
{
    std::string typeKey = "type";
    std::string typeValue = "Test";
    std::string dataKey = "data";
    std::string dataMemberKey = "name";
    std::string dataMemberValue = "Sam";

    // {"type":"Test","data":{"name":"Sam"}}
    std::string json = "{\"" + typeKey + "\":\"" + typeValue +
            "\",\"" + dataKey + "\":{\"" + dataMemberKey + "\":\"" + dataMemberValue +"\"}}";

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

    // {"type":"Test","data":{"name":"Sam"}}
    std::string json = "{\"" + typeKey + "\":\"" + typeValue +
                       "\",\"" + dataKey + "\":{\"" + dataMemberKey + "\":\"" + dataMemberValue +"\"}}";

    Message message;
    message.loadJSON(json);

    std::string result = message.getJSON();
    std::string type = message.getMember("type");
    std::string name = message.getDataMember("name");

    REQUIRE(type == typeValue);
    REQUIRE(name == dataMemberValue);
    REQUIRE(result == json);
}

TEST_CASE("Missing Key")
{
    std::string json = R"({"type":"test","data":{}})";
    std::string expectedException = R"(The key 'name' doesn't exist on the JSON document)";

    try
    {
        AuthMessage message(json);
    }
    catch(const std::invalid_argument &ex)
    {
        std::cout << ex.what() << std::endl;
        REQUIRE(ex.what() == expectedException);
    }
}

TEST_CASE("Empty Value")
{
    std::string json = R"({"type":"test","data":{"name":"","clientID":""}})";
    std::string expectedException = R"(The key 'name' exists but the value is empty)";

    try
    {
        AuthMessage message(json);
    }
    catch(const std::invalid_argument &ex)
    {
        std::cout << ex.what() << std::endl;
        REQUIRE(ex.what() == expectedException);
    }
}