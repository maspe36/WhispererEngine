# Download and unpack googletest at configure time
configure_file(libs/googletest/CMakeLists.txt googletest-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test/googletest-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/test/googletest-download")

# Add googletest directly to our build. This adds
# the following targets: gtest, gtest_main, gmock
# and gmock_main
add_subdirectory("${CMAKE_BINARY_DIR}/googletest-src"
        "${CMAKE_BINARY_DIR}/googletest-build")

# Now simply link your own targets against gtest, gmock,
# etc. as appropriate
set(TEST_SOURCE_FILES
        src/WhispererEngine_test.cpp
        src/Game/Core/Card_test.cpp)
add_executable(unit-tests ${TEST_SOURCE_FILES})
target_link_libraries(unit-tests gtest gmock)
add_test(NAME unit-tests COMMAND unit-tests)