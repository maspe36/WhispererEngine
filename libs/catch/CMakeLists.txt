cmake_minimum_required(VERSION 3.9.3)

project(catch-download NONE)

include(ExternalProject)
ExternalProject_Add(catch
        GIT_REPOSITORY https://github.com/philsquared/Catch.git
        GIT_TAG master
        SOURCE_DIR "${CMAKE_BINARY_DIR}/catch-src"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND "")