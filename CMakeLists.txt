cmake_minimum_required(VERSION 3.14)
project(AVM)

set(CMAKE_CXX_STANDARD 11)

add_executable(AVM main.cpp include/IOperand.h include/Operand.h)