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

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  # Compile preprocessor commands
  add_compile_definitions(
    VGE_PLATFORM_LINUX
    VGE_BUILD_SHARED
    )
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions(VGE_DEBUG)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(VGE_RELEASE)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Dist")
  add_compile_definitions(VGE_DIST)
endif()

# Source subdirectories/includes
include_directories(src/)
add_subdirectory(src/)

############################################
# test target executable
add_executable(test
  test/Sandbox.cpp)

target_link_libraries(
  test PRIVATE
  violetgl
  spdlog::spdlog
  )

############################################
