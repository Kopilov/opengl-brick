cmake_minimum_required(VERSION 2.8)

project(brick)

set(LIBS_DIR /usr/lib/x86_64-linux-gnu)
set(ASSIMP_LIBRARY ${LIBS_DIR}/libassimp.so.4)
set(GLFW_LIBRARY ${LIBS_DIR}/libglfw.so)

add_library(glad STATIC glad.c)
add_library(mesh STATIC mesh.cpp)
add_library(stb_image STATIC stb_image.cpp)
add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}  ${ASSIMP_LIBRARY} glad ${GLFW_LIBRARY} mesh stb_image ${CMAKE_DL_LIBS})
