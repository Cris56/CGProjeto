cmake_minimum_required(VERSION 3.24)
project(Generator)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Generator
        box.cpp
        box.hpp
        cone.cpp
        cone.hpp
        generator.cpp
        generator.h
        plane.cpp
        plane.hpp
        sphere.cpp
        sphere.hpp
        geometry.hpp)
