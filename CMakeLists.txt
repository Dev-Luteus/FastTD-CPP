cmake_minimum_required(VERSION 3.30)
project(FastTD)

set(CMAKE_CXX_STANDARD 20)

# Add the include directory for headers
include_directories(${CMAKE_SOURCE_DIR}/include)
link_directories(${CMAKE_SOURCE_DIR}/lib)

add_executable(FastTD main.cpp
        game.cpp
        include/game.h
        include/cell.h
        grid.cpp
        include/grid.h
        obstacles.cpp
        include/obstacles.h
        spire.cpp
        include/spire.h
        EnemySpawner.cpp
        include/EnemySpawner.h
        include/Enemy.h
        enemy.cpp
        include/pathNode.h
        include/PathFinder.h
        pathFinder.cpp
        include/wall.h
        wall.cpp
        include/handleMouse.h
        handleMouse.cpp
        include/gameCamera.h
        gameCamera.cpp
        include/player.h
        include/roundManager.h
        include/Logger.h
        include/timer.h
)

# Link Raylib library (and required Windows libraries)
target_link_libraries(FastTD raylib winmm)