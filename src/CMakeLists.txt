cmake_minimum_required(VERSION 3.16)
project(violet_GL_engine)

find_package(spdlog REQUIRED)

set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(violetgl
  Violet/Application.cpp
  Violet/Log.cpp
  Violet/LayerStack.cpp
  Violet/Layer.cpp
  Violet/Platform/Linux/LinuxWindow.cpp
  vgepch.hpp)

target_precompile_headers(violetgl PRIVATE
  vgepch.hpp
  )

target_link_libraries(violetgl PRIVATE
  spdlog::spdlog)
