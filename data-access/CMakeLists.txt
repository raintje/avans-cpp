CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(data-access)

SET(CMAKE_CXX_STANDARD 20)

ADD_LIBRARY(${PROJECT_NAME} SHARED
        include/db_handler.h
        src/db_handler.cc
        src/faction_handler.cc
        include/faction_handler.h)

FIND_PACKAGE(SQLite3 REQUIRED)

TARGET_LINK_LIBRARIES(${PROJECT_NAME} PRIVATE
        ${SQLite3_LIBRARIES})

TARGET_INCLUDE_DIRECTORIES(${PROJECT_NAME} PUBLIC include
        PRIVATE ${SQLite3_INCLUDE_DIRS})

FILE(COPY "${CMAKE_CURRENT_SOURCE_DIR}/paard en zwaard.db"
        DESTINATION ${INSTALL_DIR})
