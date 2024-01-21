CMAKE_MINIMUM_REQUIRED(VERSION 3.22)
PROJECT(game)

SET(CMAKE_CXX_STANDARD 20)

ADD_EXECUTABLE(${PROJECT_NAME}
        src/main.cc
        src/state/game.cc
        src/command/move_command.cc
        src/logic/movement_controller.cc
        src/logic/battle_controller.cc
        src/drawing/domain.cc
        src/drawing/hud.cc
        src/drawing/logic.cc
)

target_include_directories(${PROJECT_NAME} PRIVATE
        headers)

target_link_libraries(${PROJECT_NAME} PRIVATE
        db
        util
        domain)