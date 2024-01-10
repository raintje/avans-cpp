CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(domain)

SET(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} SHARED
        src/province.cc
        src/world.cc
        src/player.cc
        src/mountain.cc
        src/village.cc
        src/city.cc
)

target_include_directories(${PROJECT_NAME} PUBLIC
        include)

target_link_libraries(${PROJECT_NAME} PRIVATE
        util)
