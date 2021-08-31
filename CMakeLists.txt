cmake_minimum_required(VERSION 3.16)
project(violet_GL)

# custom set variables
#set(CMAKE_BUILD_TYPE "Debug")

# Library subdirectories
add_subdirectory(lib/spdlog/)
include_directories(lib/spdlog/)
add_subdirectory(lib/glfw/)
include_directories(lib/glfw/include/)
add_subdirectory(lib/glad/)
include_directories(lib/glad/include/)
add_subdirectory(lib/imgui)
include_directories(lib/imgui/)
add_subdirectory(lib/glm/)
include_directories(lib/glm/include/)

# cmake options
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

set(CMAKE_CXX_STANDARD 20)

# preproccessor definitions
add_compile_definitions(GLFW_INCLUDE_NONE)

if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  # Compile preprocessor commands
  add_compile_definitions(
    VGE_PLATFORM_LINUX
    VGE_BUILD_SHARED
    IMGUI_IMPL_OPENGL_LOADER_GLAD
    )
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Debug")
  add_compile_definitions(
    VGE_DEBUG
    VGE_ENABLE_ASSERTS
    )
  add_compile_options(-Wall -O0)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Release")
  add_compile_definitions(VGE_RELEASE)
  add_compile_options(-O2)
elseif(${CMAKE_BUILD_TYPE} STREQUAL "Dist")
  add_compile_definitions(VGE_DIST)
  add_compile_options(-O4)
endif()

# Source subdirectories/includes
include_directories(include/)
add_subdirectory(src/)

############################################
# test target executable
add_executable(test
  test/Sandbox.cpp)

target_link_libraries(
  test PRIVATE
  violetgl
  )

############################################
