cmake_minimum_required(VERSION 3.10)

project(SDL2GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(include include/ECS include/ECS/GameSpecific)

file(GLOB_RECURSE SOURCES "src/*.cpp" "src/ECS/*.cpp" "src/ECS/GameSpecific/*.cpp" "main.cpp")

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)

add_executable(SDL2GameEngine ${SOURCES})

target_link_libraries(SDL2GameEngine SDL2::SDL2 SDL2::SDL2main SDL2_ttf::SDL2_ttf SDL2_mixer::SDL2_mixer)