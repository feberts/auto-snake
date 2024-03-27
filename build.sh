#!/bin/bash

g++ -std=c++17 -Wall -Wextra -pedantic -o snake \
    src/*.cpp \
    -I curses_utilities \
    curses_utilities/pathfinder.cpp \
    curses_utilities/position.cpp \
    curses_utilities/print.cpp \
    -I graph \
    graph/graph.cpp \
    -lncurses
