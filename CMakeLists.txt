cmake_minimum_required(VERSION 3.10)

project(kmem)

# We don't actually need a higher version of the c-standard, but it's nice to have it.
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED true)

add_executable(kmem kmemory.h main.c)
