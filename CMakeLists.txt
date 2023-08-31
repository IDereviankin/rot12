cmake_minimum_required(VERSION 3.26)
project(
        rot12
        VERSION 1.0.0
        LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)
FetchContent_Declare(
        cxxopts
        URL https://github.com/jarro2783/cxxopts/archive/refs/tags/v3.1.1.zip
)
FetchContent_MakeAvailable(cxxopts)

add_executable(rot12 main.cpp)
target_link_libraries(rot12 PRIVATE cxxopts::cxxopts)