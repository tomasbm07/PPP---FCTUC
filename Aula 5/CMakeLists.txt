cmake_minimum_required(VERSION 3.15)
project(Aula_5 C)

set(CMAKE_C_STANDARD 11)

add_executable(Aula_5 main.c mp.c)

set(CMAKE_C_FLAGS ${CMKAKE_C_FLAGS} "-Wall -Wextra")
