//
// Created by Sam on 10/7/2017.
//

#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Network/Message.h"


TEST_CASE("Verify JSON format")
{
    std::string correctJSON = R"({"type":"test","data":"Does this test pass?"})";

    Message message("test", "Does this test pass?");
    std::string createdJSON = message.exportJSON();

    REQUIRE(correctJSON == createdJSON);
}
