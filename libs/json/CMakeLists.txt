cmake_minimum_required(VERSION 3.9.3)

project(json-download NONE)

include(ExternalProject)
ExternalProject_Add(json
        GIT_REPOSITORY https://github.com/nlohmann/json
        GIT_TAG v3.1.1
        SOURCE_DIR "${CMAKE_BINARY_DIR}/json-src"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND "")