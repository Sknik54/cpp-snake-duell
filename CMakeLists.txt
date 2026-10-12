project(Projekt4snake)

cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 20)

add_executable(Projekt4snake
        Schlange.cpp
        Schlange.h
        Schlangenglied.cpp
        Schlangenglied.h
        Point2d.cpp
        Point2d.h
        "main(3).cpp"
        Spielzustand.cpp)
