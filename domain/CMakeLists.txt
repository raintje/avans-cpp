CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(domain)

SET(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} SHARED
        src/province.cc
        src/land.cc
        src/player.cc
        src/enemy.cc
        src/king.cc
        src/tile.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include)

target_link_libraries(${PROJECT_NAME} PRIVATE
        db
        util)
