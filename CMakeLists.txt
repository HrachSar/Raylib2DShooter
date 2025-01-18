cmake_minimum_required(VERSION 3.3) # FetchContent is available in 3.11+
project(2D_Shooter)

# Generate compile_commands.json
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Dependencies
set(RAYLIB_VERSION 5.5)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            DOWNLOAD_EXTRACT_TIMESTAMP OFF
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_MakeAvailable(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    endif()
endif()

# Our Project

add_executable(${PROJECT_NAME} src/core/main.cpp
        src/core/game_object.cpp
        src/core/game_object.h
        src/core/player.cpp
        src/core/player.h
        src/resources/sprite_renderer.cpp
        src/resources/sprite_renderer.h
        src/core/game.cpp
        src/core/game.h
        src/core/grid.cpp
        src/core/grid.h
        src/resources/perlin.h
        src/resources/aStarPathFinder.cpp
        src/resources/aStarPathFinder.h
        src/core/enemy.cpp
        src/core/enemy.h
        src/resources/stack.cpp
        src/resources/stack.h
)
#set(raylib_VERBOSE 1)
target_link_libraries(${PROJECT_NAME} raylib)


# Checks if OSX and links appropriate frameworks (Only required on MacOS)
if (APPLE)
    target_link_libraries(${PROJECT_NAME} "-framework IOKit")
    target_link_libraries(${PROJECT_NAME} "-framework Cocoa")
    target_link_libraries(${PROJECT_NAME} "-framework OpenGL")
endif()