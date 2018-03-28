cmake_minimum_required(VERSION 3.9.3)
project(WhispererEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add the compiler flag
set(HYPOT_FLAG "-D_hypot=hypot")
add_definitions(${HYPOT_FLAG})

# Determine platform specific libs
if(WIN32)
    set(PLATFORM_LIBS wsock32 ws2_32)
else()
    set(PLATFORM_LIBS "")
endif()

link_libraries(${PLATFORM_LIBS})

# Download catch test framework
configure_file(libs/catch/CMakeLists.txt catch-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/catch-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/catch-download")

# Download pybind11
configure_file(libs/pybind11/CMakeLists.txt pybind11-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/pybind11-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/pybind11-download")

# Download json
configure_file(libs/json/CMakeLists.txt json-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/json-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/json-download")

# Include downloaded directories
include_directories(${CMAKE_BINARY_DIR}/catch-src)
add_subdirectory(${CMAKE_BINARY_DIR}/pybind11-src)
include_directories(${CMAKE_BINARY_DIR}/json-src/single_include)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.65.1 REQUIRED system thread)

# Include boost directories
include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

# Find Postgres
find_package(PostgreSQL 9.6.7 REQUIRED)

# Inclue and link Postgres
include_directories(${PostgreSQL_INCLUDE_DIRS})
link_libraries(${PostgreSQL_LIBRARIES})

# Find CURL
find_package(CURL REQUIRED)

# Include and link CURL
include_directories(${CURL_INCLUDE_DIRS})
link_libraries(${CURL_LIBRARIES})

# Add pybind11 modules
set(PYBIND11_CPP_STANDARD -std=c++17)

#pybind11_add_module(<module name> [<module source files>, ...])
pybind11_add_module(Whisperer
        include/Game/Python/Module.h
        src/Game/Card.cpp
        src/Game/Mana.cpp
        src/Game/Utilities/Taggable.cpp
        src/Game/Utilities/Exportable.cpp
        src/Game/Card/Constant.cpp
        src/Game/Card/Creature.cpp)

# Define the default libraries to include with the targets
set(DEFAULT_LIBS pybind11::embed ${Boost_LIBRARIES})

# All the headers and source code for classes used in the core game
set(WHISPERER_FILES
        src/Game/Modifier.cpp
        include/Game/Modifier.h

        src/Game/Board.cpp
        include/Game/Board.h

        src/Game/Card.cpp
        include/Game/Card.h

        src/Game/Container.cpp
        include/Game/Container.h

        src/Game/Effect.cpp
        include/Game/Effect.h

        src/Game/Event.cpp
        include/Game/Event.h

        src/Game/Game.cpp
        include/Game/Game.h

        src/Game/Mana.cpp
        include/Game/Mana.h

        src/Game/Player.cpp
        include/Game/Player.h

        src/Game/Container/Deck.cpp
        include/Game/Container/Deck.h

        src/Game/Container/Graveyard.cpp
        include/Game/Container/Graveyard.h

        src/Game/Container/Hand.cpp
        include/Game/Container/Hand.h

        src/Game/Container/CreatureZone.cpp
        include/Game/Container/CreatureZone.h

        src/Game/Card/Constant.cpp
        include/Game/Card/Constant.h

        src/Game/Card/Creature.cpp
        include/Game/Card/Creature.h

        src/Game/Card/Spell.cpp
        include/Game/Card/Spell.h

        src/Game/Event/Game/EndTurnEvent.cpp
        include/Game/Event/Game/EndTurnEvent.h

        src/Game/Event/Game/StartGameEvent.cpp
        include/Game/Event/Game/StartGameEvent.h

        src/Game/Event/Game/StartTurnEvent.cpp
        include/Game/Event/Game/StartTurnEvent.h

        src/Game/Event/Player/DrawEvent.cpp
        include/Game/Event/Player/DrawEvent.h

        src/Game/Event/Player/PlayCardEvent.cpp
        include/Game/Event/Player/PlayCardEvent.h

        src/Game/Event/Player/PlayerAttackedEvent.cpp
        include/Game/Event/Player/PlayerAttackedEvent.h

        src/Game/Python/Factory.cpp
        include/Game/Python/Factory.h

        src/Game/Python/Version.cpp
        include/Game/Python/Version.h

        src/Network/Client.cpp
        include/Network/Client.h

        src/Network/Message.cpp
        include/Network/Message.h

        src/Network/Server.cpp
        include/Network/Server.h

        src/Network/HTTPRequest.cpp
        include/Network/HTTPRequest.h

        include/Network/Message/AuthMessage.h
        src/Network/Messsage/AuthMessage.cpp

        src/Network/Messsage/CardMovedMessage.cpp
        include/Network/Message/CardMovedMessage.h

        src/Network/Messsage/ChatMessage.cpp
        include/Network/Message/ChatMessage.h

        src/Network/Messsage/DrawMessage.cpp
        include/Network/Message/DrawMessage.h

        src/Network/Messsage/EndTurnMessage.cpp
        include/Network/Message/EndTurnMessage.h

        src/Network/Messsage/FightPlayerMessage.cpp
        include/Network/Message/FightPlayerMessage.h

        src/Network/Messsage/PlayCardMessage.cpp
        include/Network/Message/PlayCardMessage.h

        src/Network/Messsage/PlayerAttackedMessage.cpp
        include/Network/Message/PlayerAttackedMessage.h

        src/Network/Messsage/QueueMessage.cpp
        include/Network/Message/QueueMessage.h

        src/Network/Messsage/StartGameMessage.cpp
        include/Network/Message/StartGameMessage.h

        src/Network/Messsage/StartTurnMessage.cpp
        include/Network/Message/StartTurnMessage.h

        src/Network/Exceptions/JSONError.cpp
        include/Network/Exceptions/JSONError.h

        src/Game/Utilities/Taggable.cpp
        include/Game/Utilities/Taggable.h

        src/Game/Utilities/Exportable.cpp
        include/Game/Utilities/Exportable.h

        src/Game/Utilities/Database.cpp
        include/Game/Utilities/Database.h)

# All source files and the entry point
set(SOURCE_FILES
        src/WhispererEngine.cpp
        ${WHISPERER_FILES})

# Define the WhispererEngine target
add_executable(WhispererEngine ${SOURCE_FILES})
target_include_directories(WhispererEngine PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(WhispererEngine PRIVATE ${DEFAULT_LIBS} ${PLATFORM_LIBS} ${CMAKE_THREAD_LIBS_INIT})

# All headers and source files for the game, with the unit tests, and the catch main
set(TEST_FILES
        ${WHISPERER_FILES}
        tests/CatchMain.cpp
        tests/Game/test_Card.cpp
        tests/Game/test_Player.cpp
        tests/Game/Card/test_Creature.cpp
        tests/Game/Python/test_Factory.cpp
        tests/Game/Python/test_Integration.cpp
        tests/Game/Utilities/test_Database.cpp
        tests/Network/test_Message.cpp
        tests/Network/test_HTTPRequest.cpp)

# Define the WhispererEngineTests target
add_executable(WhispererEngineTests ${TEST_FILES})
target_include_directories(WhispererEngineTests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(WhispererEngineTests PRIVATE ${DEFAULT_LIBS} ${PLATFORM_LIBS} ${CMAKE_THREAD_LIBS_INIT})