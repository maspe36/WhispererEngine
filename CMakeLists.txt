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

# Download rapidjson
configure_file(libs/rapidjson/CMakeLists.txt rapidjson-download/CMakeLists.txt)
execute_process(COMMAND "${CMAKE_COMMAND}" -G "${CMAKE_GENERATOR}" .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/rapidjson-download")
execute_process(COMMAND "${CMAKE_COMMAND}" --build .
        WORKING_DIRECTORY "${CMAKE_BINARY_DIR}/rapidjson-download")

# Include downloaded directories
include_directories(${CMAKE_BINARY_DIR}/catch-src)
add_subdirectory(${CMAKE_BINARY_DIR}/pybind11-src)
add_subdirectory(${CMAKE_BINARY_DIR}/rapidjson-src)

set(Boost_USE_STATIC_LIBS        ON)
set(Boost_USE_MULTITHREADED      ON)
set(Boost_USE_STATIC_RUNTIME    OFF)
find_package(Boost 1.65.1 REQUIRED system thread)

# Include boost directories
include_directories(${Boost_INCLUDE_DIRS})
link_libraries(${Boost_LIBRARIES})

# Add pybind11 modules
set(PYBIND11_CPP_STANDARD -std=c++17)

#pybind11_add_module(<module name> [<module source files>, ...])
pybind11_add_module(Whisperer
        include/Game/Python/Module.h
        src/Game/Core/Card.cpp
        src/Game/Core/Mana.cpp
        src/Game/Utilities/Taggable.cpp
        src/Game/Derived/Card/Constant.cpp
        src/Game/Derived/Card/Creature.cpp)

# Define the default libraries to include with the targets
set(DEFAULT_LIBS pybind11::embed ${Boost_LIBRARIES})

# All the headers and source code for classes used in the core game
set(WHISPERER_FILES
        src/Game/Core/Modifier.cpp
        include/Game/Core/Modifier.h

        src/Game/Core/Board.cpp
        include/Game/Core/Board.h

        src/Game/Core/Card.cpp
        include/Game/Core/Card.h

        src/Game/Core/Effect.cpp
        include/Game/Core/Effect.h

        src/Game/Core/Event.cpp
        include/Game/Core/Event.h

        src/Game/Core/Game.cpp
        include/Game/Core/Game.h

        src/Game/Core/Mana.cpp
        include/Game/Core/Mana.h

        src/Game/Core/Player.cpp
        include/Game/Core/Player.h

        src/Game/Derived/Card/Constant.cpp
        include/Game/Derived/Card/Constant.h

        src/Game/Derived/Card/Creature.cpp
        include/Game/Derived/Card/Creature.h

        src/Game/Derived/Card/Spell.cpp
        include/Game/Derived/Card/Spell.h

        src/Game/Derived/Effect/TriggerEffect.cpp
        include/Game/Derived/Effect/TriggerEffect.h

        src/Game/Derived/Effect/AuraEffect.cpp
        include/Game/Derived/Effect/AuraEffect.h

        src/Game/Derived/Event/GameEvents/DeadEvent.cpp
        include/Game/Derived/Event/GameEvents/DeadEvent.h

        src/Game/Derived/Event/GameEvents/DrawEvent.cpp
        include/Game/Derived/Event/GameEvents/DrawEvent.h

        src/Game/Derived/Event/PlayerEvents/AttackEvent.cpp
        include/Game/Derived/Event/PlayerEvents/AttackEvent.h

        src/Game/Derived/Event/PlayerEvents/DamageEvent.cpp
        include/Game/Derived/Event/PlayerEvents/DamageEvent.h

        src/Game/Derived/Event/PlayerEvents/HealEvent.cpp
        include/Game/Derived/Event/PlayerEvents/HealEvent.h

        src/Game/Derived/Event/PlayerEvents/DestroyEvent.cpp
        include/Game/Derived/Event/PlayerEvents/DestroyEvent.h

        src/Game/Derived/Event/PlayerEvents/PlayEvent.cpp
        include/Game/Derived/Event/PlayerEvents/PlayEvent.h

        src/Game/Derived/Event/PlayerEvents/SelectionEvent.cpp
        include/Game/Derived/Event/PlayerEvents/SelectionEvent.h

        src/Game/Python/Factory.cpp
        include/Game/Python/Factory.h

        src/Game/Python/Version.cpp
        include/Game/Python/Version.h

        src/Network/Client.cpp
        include/Network/Client.h

        src/Network/Server.cpp
        include/Network/Server.h

        src/Game/Utilities/Exportable.cpp
        include/Game/Utilities/Exportable.h

        src/Game/Utilities/Taggable.cpp
        include/Game/Utilities/Taggable.h)

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
        tests/Game/Core/test_Card.cpp
        tests/Game/Python/test_Factory.cpp
        tests/Game/Python/test_Integration.cpp)

# Define the WhispererEngineTests target
add_executable(WhispererEngineTests ${TEST_FILES})
target_include_directories(WhispererEngineTests PRIVATE ${Boost_INCLUDE_DIRS})
target_link_libraries(WhispererEngineTests PRIVATE ${DEFAULT_LIBS} ${PLATFORM_LIBS} ${CMAKE_THREAD_LIBS_INIT})