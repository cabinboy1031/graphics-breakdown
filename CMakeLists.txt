cmake_minimum_required(VERSION 3.10)
project(violet_GL)

set(OpenGL_GL_PREFERENCE "GLVND")
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_compile_definitions(VGE_PLATFORM_LINUX)

include_directories(src/)
add_subdirectory(src/)

add_executable(test
  test/Sandbox.cpp)

target_link_libraries(
  test
  violetgl
  )
