cmake_minimum_required (VERSION 3.8)
project ("JJEngine")

set(CMAKE_CXX_STANDARD 20)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory("thirdparty/glad")
add_subdirectory("thirdparty/glfw")
add_subdirectory("thirdparty/glm")

add_library(${PROJECT_NAME} "src/Window.cpp")

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} glad)
target_link_libraries(${PROJECT_NAME} glm)

target_include_directories(${PROJECT_NAME} PUBLIC "include")