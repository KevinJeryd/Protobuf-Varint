cmake_minimum_required(VERSION 3.12)
project(ProtobufVarint)

set(CMAKE_CXX_STANDARD 20)

add_executable(ProtobufVarint main.cpp)

target_include_directories(ProtobufVarint PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)