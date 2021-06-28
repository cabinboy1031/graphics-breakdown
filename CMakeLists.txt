cmake_minimum_required(VERSION 3.10)
project(violet_GL)

# library packages
set(OpenGL_GL_PREFERENCE "GLVND")
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Library subdirectories
add_subdirectory(lib/spdlog/)

# cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Compile preprocessor commands
add_compile_definitions(VGE_PLATFORM_LINUX)

# Source subdirectories/includes
include_directories(src/)
add_subdirectory(src/)


# test target executable
add_executable(test
  test/Sandbox.cpp)

target_link_libraries(
  test PRIVATE
  violetgl
  spdlog::spdlog
  )

######################
