cmake_minimum_required(VERSION 3.9.3)

project(rapidjson-download NONE)

include(ExternalProject)
ExternalProject_Add(rapidjson
        GIT_REPOSITORY https://github.com/Tencent/rapidjson
        GIT_TAG v1.1.0
        SOURCE_DIR "${CMAKE_BINARY_DIR}/rapidjson-src"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND "")