cmake_minimum_required(VERSION 3.10)
project(SlitherPro C)

set(CMAKE_C_STANDARD 99)

find_package(PkgConfig REQUIRED)

set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)

include(FetchContent)
set(FETCHCONTENT_QUIET OFF)

FetchContent_Declare(
    enet
    GIT_REPOSITORY https://github.com/zpl-c/enet.git
    GIT_TAG v2.6.5
    GIT_SHALLOW FALSE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(enet)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 5.5
    GIT_SHALLOW FALSE
    GIT_PROGRESS TRUE
)
FetchContent_MakeAvailable(raylib)

include_directories(src/common)

add_executable(server src/server/main.c)
target_link_libraries(server PRIVATE enet_static m)

add_executable(client src/client/main.c)
target_link_libraries(client PRIVATE raylib enet_static m)

enable_testing()
add_executable(test_game tests/test_game.c)
target_include_directories(test_game PRIVATE tests)
target_link_libraries(test_game PRIVATE m)
add_test(NAME game_tests COMMAND test_game)