cmake_minimum_required(VERSION 3.8)
project(WhispererEngine)

set(CMAKE_CXX_STANDARD 17)

# Add pybind11
set(PYBIND11_CPP_STANDARD -std=c++1z)
add_subdirectory(libs/pybind11)
#pybind11_add_module(<module name> [<module source files>, ...])

# Add the hypot flag
set(GCC_HYPOT_FLAGS "-D_hypot=hypot")
add_definitions( ${GCC_HYPOT_FLAGS} )

# Add the ms win flag
set(GCC_MS64_FLAGS "-D MS_WIN64")
add_definitions( ${GCC_HYPOT_FLAGS} )

set(SOURCE_FILES
        src/WhispererEngine.cpp

        src/Game/Core/Event.cpp
        include/Game/Core/Event.h

        src/Game/Core/Affect.cpp
        include/Game/Core/Affect.h

        src/Game/Core/Board.cpp
        include/Game/Core/Board.h

        src/Game/Core/Card.cpp
        include/Game/Core/Card.h

        src/Game/Core/Game.cpp
        include/Game/Core/Game.h

        src/Game/Core/Mana.cpp
        include/Game/Core/Mana.h

        src/Game/Core/Player.cpp
        include/Game/Core/Player.h

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

        src/Game/Derived/Card/Constant.cpp
        include/Game/Derived/Card/Constant.h

        src/Game/Derived/Card/Creature.cpp
        include/Game/Derived/Card/Creature.h

        src/Game/Derived/Card/Spell.cpp
        include/Game/Derived/Card/Spell.h

        src/Game/PythonInterface/Factory.cpp
        include/Game/PythonInterface/Factory.h

        src/Game/PythonInterface/Converter.cpp
        include/Game/PythonInterface/Converter.h

        src/Network/Client.cpp
        include/Network/Client.h

        src/Network/Server.cpp
        include/Network/Server.h)

add_executable(WhispererEngine ${SOURCE_FILES})
target_link_libraries(WhispererEngine PRIVATE pybind11::embed)