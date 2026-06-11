cmake_minimum_required(VERSION 3.14)
project(targets)
find_package(raylib QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG 5.5
        GIT_SHALLOW TRUE
    )

    FetchContent_MakeAvailable(raylib)
endif()

file(GLOB SOURCES
    src/*.cpp
)

add_executable(targets ${SOURCES})
target_compile_features(targets PRIVATE cxx_std_17)
target_link_libraries(targets PRIVATE raylib)