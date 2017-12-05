//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"

#include "../../../include/Game/Python/Factory.h"
#include "../../../include/Game/Python/Version.h"

TEST_CASE("Create factory")
{
    Factory factory;

    SECTION("Verify minimum python version")
    {
        std::string minimumVersion = "2.7";
        Version version(minimumVersion);
        bool versionCheck = version < *factory.version;
        REQUIRE(versionCheck);
    }

    SECTION("Verify expected python version")
    {
        std::string expectedVersion = "3.6.3";
        Version version(expectedVersion);
        bool versionCheck = version == *factory.version;

        if (!versionCheck)
        {
            FAIL_CHECK("Unexpected python version, expected " + expectedVersion +
                               " but factory's interpreter is running " + factory.version->toString());
        }
    }
}
