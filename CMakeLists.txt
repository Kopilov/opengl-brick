cmake_minimum_required(VERSION 2.8)

project(brick)

#find_package(assimp REQUIRED)
add_subdirectory(assimp)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

add_library(glad STATIC glad.c)
add_library(mesh STATIC mesh.cpp)
target_include_directories(mesh PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/assimp/include)
target_link_libraries(mesh assimp)

add_library(stb_image STATIC stb_image.cpp)

add_executable(${PROJECT_NAME} "main.cpp")

target_link_libraries(${PROJECT_NAME} assimp glad glfw glm mesh stb_image ${CMAKE_DL_LIBS})
