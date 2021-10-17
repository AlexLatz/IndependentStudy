cmake_minimum_required(VERSION 3.20)
project(Clickomania)

set(CMAKE_CXX_STANDARD 17)

SET(TARGET_H
        Grid.h
        GameState.h
        )
# Local source files here
SET(TARGET_SRC
        Grid.cpp
        GameState.cpp
        )


add_executable(Clickomania clickomania.cpp ${TARGET_SRC} ${TARGET_H})
add_executable(Clickomania_singlefile singlefile.cpp singlefile.cpp)
