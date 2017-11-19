//
// Created by Sam on 11/18/2017.
//

#include "../../../build/catch-src/include/catch.hpp"

#include "../../../include/Game/Python/Factory.h"

TEST_CASE("Create factory")
{
    auto* factory = new Factory();

    SECTION("Verify minimum python version")
    {
        std::string minimumVersion = "2.7";
        bool versionCheck = Version(minimumVersion) < factory->version;
        REQUIRE(versionCheck);
    }

    SECTION("Verify expected python version")
    {
        std::string expectedVersion = "3.6.3";
        bool versionCheck = Version(expectedVersion) == factory->version;

        if (!versionCheck)
        {
            FAIL_CHECK("Unexpected python version, expected " + expectedVersion +
                               " but factory's interpreter is running " + factory->version.toString());
        }
    }

    delete factory;
}