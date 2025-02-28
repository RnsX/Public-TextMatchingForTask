cmake_minimum_required(VERSION 3.27)
project(TextMatchingTest)

set(CMAKE_CXX_STANDARD 23)

add_executable(TextMatchingTest main.cpp
        ClassicFuzzyMatching.cpp
        ClassicFuzzyMatching.h
        TokenBasedMatching.cpp
        TokenBasedMatching.h
)
