cmake_minimum_required(VERSION 3.20)
project(Checkers)

set(CMAKE_CXX_STANDARD 17)

SET(TARGET_H
        Checkers.h
        Board.h
        GameState.h
        )
# Local source files here
SET(TARGET_SRC
        Board.cpp
        GameState.cpp
        )


add_executable(Checkers Checkers.cpp ${TARGET_SRC} ${TARGET_H})
project(singlefile)
add_executable(singlefile singlefile.cpp)
