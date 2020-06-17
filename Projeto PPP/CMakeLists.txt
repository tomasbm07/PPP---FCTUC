cmake_minimum_required(VERSION 3.15)

project(Projeto_PPP C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS ${CMKAKE_C_FLAGS} "-Wall -Wextra")

add_executable(Projeto_PPP main.c Lista.c Lista.h)