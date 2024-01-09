CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(domain)

SET(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} SHARED
        src/province.cc
        src/world.cc
        src/tile.cc
        src/player.cc
        include/interface/tile_contents.h
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include)

target_link_libraries(${PROJECT_NAME} PRIVATE
        util)
