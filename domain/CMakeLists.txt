CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(Domain)

SET(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} SHARED
        src/faction.cc
        include/faction.h

        src/troops.cc
        include/troops.h

        include/troops_type.h

        src/province.cc
        include/province.h

        src/world.cc
        include/world.h

        src/city.cc
        include/city.h

        src/village.cc
        include/village.h

        src/mountain.cc
        include/mountain.h)

target_include_directories(${PROJECT_NAME} PUBLIC
        include)
