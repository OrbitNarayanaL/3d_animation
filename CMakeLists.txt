cmake_minimum_required(VERSION 3.20)
project(ThreeDCharacterCreator VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# For Python modules
set(PYTHON_MODULE_DIR ${CMAKE_SOURCE_DIR}/python/api)
file(MAKE_DIRECTORY ${PYTHON_MODULE_DIR})

# Fetch dependencies
include(FetchContent)

# GLFW
FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

# GLM
FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.1
)

# pybind11
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    GIT_TAG v2.13.6
)

FetchContent_MakeAvailable(glfw glm pybind11)

# C++ Core Library
add_library(core
    src/core/Window.cpp
    src/core/Window.h
    src/core/Renderer.cpp
    src/core/Renderer.h
    src/core/Application.cpp
    src/core/Application.h
    src/core/Mesh.cpp
    src/core/Mesh.h
    deps/glad/glad.c
    deps/glad/glad.h
)

target_include_directories(core PUBLIC
    ${CMAKE_SOURCE_DIR}/src
    ${CMAKE_SOURCE_DIR}/thirdparty
    ${CMAKE_SOURCE_DIR}/deps
    ${glm_SOURCE_DIR}
)

target_link_libraries(core PUBLIC glfw glm OpenGL::GL)

# Find OpenGL
find_package(OpenGL REQUIRED)
target_link_libraries(core PUBLIC OpenGL::GL)

# Python bindings module
pybind11_add_module(renderer
    src/bindings/pybind_module.cpp
)

target_link_libraries(renderer PRIVATE core)

# Set output directory for the Python module
set_target_properties(renderer PROPERTIES
    PREFIX ""
    SUFFIX ".pyd"
    LIBRARY_OUTPUT_DIRECTORY ${PYTHON_MODULE_DIR}
    RUNTIME_OUTPUT_DIRECTORY ${PYTHON_MODULE_DIR}
)
