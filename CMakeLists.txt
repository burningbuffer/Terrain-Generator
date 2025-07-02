cmake_minimum_required (VERSION 3.8)

project(terrain-renderer)

file(GLOB IMGUI_SOURCES "deps/imgui/*.cpp")
file(GLOB IMGUI_GLFW_BACKEND "deps/imgui/backends/imgui_impl_glfw.cpp")
file(GLOB IMGUI_OPENGL_BACKEND "deps/imgui/backends/imgui_impl_opengl3.cpp")

file(GLOB HEADERS "source/*.hpp")
file(GLOB SOURCES "source/*.cpp")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(terrain-renderer ${HEADERS} ${SOURCES} ${IMGUI_SOURCES} ${IMGUI_GLFW_BACKEND} ${IMGUI_OPENGL_BACKEND})

target_include_directories(terrain-renderer PRIVATE deps/glm 
                                                    deps/glfw/include
                                                    deps/glew/include
                                                    deps/stb
                                                    deps/imgui
                                                    deps/imgui/backends)

target_link_directories(terrain-renderer PRIVATE deps/glfw/lib-vc2019
                                                 deps/glew/lib/Release/x64)

target_link_libraries(terrain-renderer PRIVATE glfw3.lib glew32.lib opengl32.lib)

add_custom_command(TARGET terrain-renderer POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/deps/glew/bin/Release/x64/glew32.dll" "${CMAKE_BINARY_DIR}/Debug/glew32.dll" )

add_custom_command(TARGET terrain-renderer POST_BUILD 
                   COMMAND ${CMAKE_COMMAND} -E create_symlink "${CMAKE_SOURCE_DIR}/shaders" "${CMAKE_BINARY_DIR}/Debug/shaders")