cmake_minimum_required (VERSION 3.8)
project ("TestApp")

set(CMAKE_CXX_STANDARD 20)

add_executable(${PROJECT_NAME} WIN32 "src/TestApp.cpp")

set_property(
        TARGET ${PROJECT_NAME}
        APPEND
        PROPERTY ADDITIONAL_CLEAN_FILES  $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets
)

add_custom_command(TARGET ${PROJECT_NAME} PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/assets $<TARGET_FILE_DIR:${PROJECT_NAME}>/assets)

target_link_libraries(${PROJECT_NAME} JJEngine)
target_include_directories(${PROJECT_NAME} PRIVATE JJEngine)