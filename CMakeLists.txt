cmake_minimum_required(VERSION 3.0)
project(GeometrySlash CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

add_executable(GeometrySlash src/main.cpp src/gamestate.cpp src/gamestate.h src/ingame.cpp src/ingame.h src/mainmenu.cpp src/mainmenu.h src/random.cpp src/random.h)
target_link_libraries(GeometrySlash PRIVATE raylib)
