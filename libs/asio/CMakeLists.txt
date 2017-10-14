cmake_minimum_required(VERSION 3.9.3)

project(asio-download NONE)

include(ExternalProject)
ExternalProject_Add(asio
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
        GIT_TAG master
        SOURCE_DIR "${CMAKE_BINARY_DIR}/asio-src"
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        TEST_COMMAND "")