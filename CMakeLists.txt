cmake_minimum_required(VERSION 3.10)

project(SDL2GameEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set vcpkg root directory
set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake")

# Include directories
include_directories(
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/include"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/include/ECS"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/include/ECS/GameSpecific"
)

# Collect all source files
file(GLOB_RECURSE SOURCES
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/src/*.cpp"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/src/ECS/*.cpp"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/src/ECS/GameSpecific/*.cpp"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/*.cpp"
)

# Collect all header files (optional, for IDEs to show them in the project)
file(GLOB_RECURSE HEADERS
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/include/*.h"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/include/ECS/*.h"
    "${CMAKE_SOURCE_DIR}/SDL2 Game Engine/include/ECS/GameSpecific/*.h"
)

# Find SDL2 packages
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

# Add executable
add_executable(SDL2GameEngine ${SOURCES} ${HEADERS})

# Link libraries
target_link_libraries(SDL2GameEngine
    SDL2::SDL2
    SDL2::SDL2main
    SDL2_ttf::SDL2_ttf
    SDL2_mixer::SDL2_mixer
    SDL2_image::SDL2_image
)

# Post-build step to copy DLLs
add_custom_command(TARGET SDL2GameEngine POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${CMAKE_SOURCE_DIR}/vcpkg/installed/${VCPKG_TARGET_TRIPLET}/bin/SDL2.dll"
        "${CMAKE_SOURCE_DIR}/vcpkg/installed/${VCPKG_TARGET_TRIPLET}/bin/SDL2_image.dll"
        "${CMAKE_SOURCE_DIR}/vcpkg/installed/${VCPKG_TARGET_TRIPLET}/bin/SDL2_ttf.dll"
        "${CMAKE_SOURCE_DIR}/vcpkg/installed/${VCPKG_TARGET_TRIPLET}/bin/SDL2_mixer.dll"
        $<TARGET_FILE_DIR:SDL2GameEngine>
)