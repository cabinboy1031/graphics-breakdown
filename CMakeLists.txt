cmake_minimum_required(VERSION 3.16)
project(violet_GL)

# custom set variables
#set(CMAKE_BUILD_TYPE "Debug")

# Library subdirectories
add_subdirectory(lib/spdlog/)
add_subdirectory(lib/glfw/)
add_subdirectory(lib/glad/)

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
  add_compile_options(-Wall -O0)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(VGE_RELEASE)
  add_compile_options(-O2)
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
  glfw
  glad4
  )

############################################
