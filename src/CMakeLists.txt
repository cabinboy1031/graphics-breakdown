cmake_minimum_required(VERSION 3.16)
project(violet_GL_engine)

#set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(violetgl
  Violet/Application.cpp
  Violet/Log.cpp
  Violet/LayerStack.cpp
  Violet/Layer.cpp
  Violet/Platform/Linux/LinuxWindow.cpp
  Violet/Platform/OpenGL/OpenGLContext.cpp
  Violet/Platform/Linux/LinuxInput.cpp
  Violet/ImGui/ImguiLayer.cpp
  Violet/ImGui/ImguiBuild.cpp)

target_link_libraries(violetgl PRIVATE
  glad4
  glfw
  )

target_link_libraries(violetgl PUBLIC
  imgui
  glm
  spdlog
  )
