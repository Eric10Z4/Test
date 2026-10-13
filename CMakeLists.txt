cmake_minimum_required(VERSION 3.16)
project(algorithm_practice LANGUAGES CXX)
add_executable(test repo_test/test.cpp)
target_compile_features(test PRIVATE cxx_std_17)
