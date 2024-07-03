cmake_minimum_required (VERSION 3.8)
project ("TestApp")

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} WIN32 "src/TestApp.cpp")

target_link_libraries(${PROJECT_NAME} JJEngine)
target_include_directories(${PROJECT_NAME} PRIVATE JJEngine)