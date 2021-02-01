cmake_minimum_required(VERSION 3.5)

project(project-1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)
include_directories(
     D:/visual\ c++/Dependencies/glfw/include
     D:/visual\ c++/Dependencies/glew/include
     D:/visual\ c++/Dependencies/glm
)
LINK_DIRECTORIES(D:/visual\ c++/Dependencies/glfw/lib-vc2019
                 D:/visual\ c++/Dependencies/glew/lib/Release/Win32
    )
add_executable(project-1
  main.cpp stb_image.h
)
target_link_libraries(project-1 Qt5::Core glew32s opengl32 glfw3)
