cmake_minimum_required(VERSION 3.30)
project(ColorPicker)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.3.10
)
FetchContent_MakeAvailable(glfw)

add_subdirectory(imgui)
find_package(OpenGL REQUIRED)

add_executable(ColorPicker main.cpp
        GUI/GuiBuilder.cpp
        Controllers/WindowsController.cpp
        Controllers/LinuxController.cpp)

target_link_libraries(
        ColorPicker PRIVATE
        imgui
        glfw
        OpenGL::GL
)

target_include_directories(
        ColorPicker PRIVATE
        ${CMAKE_SOURCE_DIR}/GUI
        ${CMAKE_SOURCE_DIR}/Controllers
        ${CMAKE_SOURCE_DIR}/imgui
)
