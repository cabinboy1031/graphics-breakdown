cmake_minimum_required(VERSION 3.16)
project(violet_GL_engine)

#set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(violetgl
  Violet/Application.cpp
  Violet/Log.cpp
  Violet/LayerStack.cpp
  Violet/Layer.cpp
  Violet/Platform/Linux/LinuxWindow.cpp
  Violet/Platform/OpenGL/ImguiOpenGLRenderer.cpp
  Violet/ImGui/ImguiLayer.cpp)

target_link_libraries(violetgl PRIVATE
  spdlog::spdlog
  glad4
  glfw
  imgui)
