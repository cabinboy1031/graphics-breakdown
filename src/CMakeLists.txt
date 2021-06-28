cmake_minimum_required(VERSION 3.10)
project(violet_GL_engine)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(violetgl
  Violet/Application.cpp)
