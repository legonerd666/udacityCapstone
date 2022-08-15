cmake_minimum_required(VERSION 3.7)

add_definitions(-std=c++17)

set(CXX_FLAGS "-Wall")
set(CMAKE_CXX_FLAGS, "${CXX_FLAGS}")

project(CharacterCreator)

find_package(wthttp)
find_package(wt)

file(GLOB project_SRCS src/*.cpp src/classes/*.cpp src/classes/gui/*.cpp)

add_executable(CharacterCreator ${project_SRCS})

target_include_directories(CharacterCreator PRIVATE include/ include/classes/ include/classes/gui)    

TARGET_LINK_LIBRARIES(CharacterCreator
    pthread
    wthttp
    wt
)