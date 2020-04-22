cmake_minimum_required(VERSION 2.8)

project(brick)


set(LIBS_DIR /usr/lib/x86_64-linux-gnu)
set(ASSIMP_LIBRARY ${LIBS_DIR}/libassimp.so.4)
set(GLEW_LIBRARY ${LIBS_DIR}/libGLEW.so)
set(GLFW_LIBRARY ${LIBS_DIR}/libglfw.so)
set(OPENGL_LIBRARY ${LIBS_DIR}/libOpenGL.so)

add_library(mesh STATIC mesh.cpp)
add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME}  ${ASSIMP_LIBRARY} ${GLEW_LIBRARY} ${GLFW_LIBRARY} ${OPENGL_LIBRARY} mesh)
