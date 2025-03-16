cmake_minimum_required(VERSION 3.29.3)

project(LightYears
    VERSION 1.0.0
    LANGUAGES C CXX
)

set(CMAKE_CXX_STANDARD           14)
set(CMAKE_CXX_STANDARD_REQUIRED  ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(LIGHT_YEARS_GAME_TARGET_NAME LightYears.Game)
set(LIGHT_YEARS_ENGINE_TARGET_NAME LightYears.Engine)

add_subdirectory(${LIGHT_YEARS_GAME_TARGET_NAME})
add_subdirectory(${LIGHT_YEARS_ENGINE_TARGET_NAME})