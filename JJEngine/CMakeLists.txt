# CMakeList.txt : CMake project for JJEngine, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_library (JJEngine  "include/JJEngine.h" "include/Graphics/Window.h" "src/Graphics/Window.cpp")
target_include_directories(JJEngine PUBLIC include/)

target_link_libraries(JJEngine glfw)
target_link_libraries(JJEngine glad)
target_link_libraries(JJEngine glm)
target_link_libraries(JJEngine assimp)

# TODO: Add tests and install targets if needed.
