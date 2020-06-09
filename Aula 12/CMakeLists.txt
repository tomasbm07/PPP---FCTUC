cmake_minimum_required(VERSION 3.15)
project(Aula_12 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_C_FLAGS ${CMKAKE_C_FLAGS} "-Wall -Wextra")

add_executable(Aula_12 main.c maisculas.c)