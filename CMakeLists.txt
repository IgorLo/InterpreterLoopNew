cmake_minimum_required(VERSION 3.10)
project(InterpreterLoopNew C)

set(CMAKE_C_STANDARD 99)

add_executable(InterpreterLoopNew executor.c loader.c headers/loader.h utilities.c headers/utilities.h headers/tokenReader.h tokenReader.c expressions.c headers/expressions.h loop.c headers/loop.h variables.c headers/variables.h headers/executor.h)