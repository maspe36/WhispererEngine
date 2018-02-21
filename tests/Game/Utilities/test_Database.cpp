//
// Created by Sam on 11/18/2017.
//

#include <iostream>
#include "../../../build/catch-src/include/catch.hpp"
#include "../../../include/Game/Utilities/Database.h"

TEST_CASE("Create database")
{
    try
    {
        Database database;
    }
    catch(const std::exception &ex)
    {
        std::cout << ex.what() << std::endl;
    }
}
