cmake_minimum_required(VERSION 3.15)
project(Aula_2 C)

set(CMAKE_C_STANDARD 11)

add_executable(Aula_2 main.c main.c)

set(CMAKE_C_FLAGS ${CMKAKE_C_FLAGS} "-Wall -Wextra")
