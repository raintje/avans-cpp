CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(game)

SET(CMAKE_CXX_STANDARD 20)

ADD_EXECUTABLE(${PROJECT_NAME}
        src/main.cc
        src/drawing/prompt_drawer.cc
)

target_link_libraries(${PROJECT_NAME} PRIVATE
        db
        domain)