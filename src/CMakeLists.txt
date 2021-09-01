cmake_minimum_required(VERSION 3.16)
project(violet_GL_engine)

#set(CMAKE_CXX_VISIBILITY_PRESET hidden)

add_library(violetgl
  Violet/Application.cpp
  Violet/Log.cpp
  Violet/LayerStack.cpp
  Violet/Layer.cpp

  Violet/Renderer/Renderer.cpp
  Violet/Renderer/Shader.cpp
  Violet/Renderer/Buffer.cpp
  Violet/Renderer/VertexArray.cpp

  Violet/Platform/Linux/LinuxWindow.cpp
  Violet/Platform/Linux/LinuxInput.cpp

  Violet/Platform/OpenGL/OpenGLContext.cpp
  Violet/Platform/OpenGL/OpenGLBuffer.cpp
  Violet/Platform/OpenGL/OpenGLShader.cpp
  Violet/Platform/OpenGL/OpenGLVertexArray.cpp

  Violet/ImGui/ImguiLayer.cpp
  Violet/ImGui/ImguiBuild.cpp
  )

target_link_libraries(violetgl PRIVATE
  glad4
  glfw
  )

target_link_libraries(violetgl PUBLIC
  imgui
  glm
  spdlog
  )
