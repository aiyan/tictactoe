cmake_minimum_required(VERSION 3.16)

project(tictactoe)

set(CMAKE_CXX_STANDARD 20)

add_executable(tictactoe main.cpp Position.h PerfectAgent.cpp PerfectAgent.h TranspositionTable.h Benchmark.h RandomAgent.cpp RandomAgent.h Agent.h ManualAgent.cpp ManualAgent.h)
