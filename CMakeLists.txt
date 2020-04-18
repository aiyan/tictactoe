cmake_minimum_required(VERSION 3.16)

project(tictactoe)

set(CMAKE_CXX_STANDARD 20)

add_executable(tictactoe main.cpp Position.h Agent.cpp Agent.h MoveSorter.h)
