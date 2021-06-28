cmake_minimum_required(VERSION 3.10)
project(violet_GL_engine)

find_package(spdlog REQUIRED)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(violetgl
  Violet/Application.cpp
  Violet/Log.cpp)

target_link_libraries(violetgl PRIVATE
  spdlog::spdlog)
