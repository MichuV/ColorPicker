cmake_minimum_required(VERSION 3.30)
project(ColorPicker)

set(CMAKE_CXX_STANDARD 20)

# -- OpenGL --

find_package(OpenGL REQUIRED)

# -- glfw --

include(FetchContent)
FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG 3.4
)
FetchContent_MakeAvailable(glfw)

# -- imgui --

FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/ocornut/imgui.git
        GIT_TAG v1.92.4
)
FetchContent_MakeAvailable(imgui)

add_library(ImguiLib
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/imgui_demo.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

target_include_directories(ImguiLib PUBLIC
        ${imgui_SOURCE_DIR}
        ${imgui_SOURCE_DIR}/backends
        ${glfw_SOURCE_DIR}/include
)

target_link_libraries(
        ImguiLib PUBLIC
        glfw
        OpenGL::GL
)

add_executable(ColorPicker main.cpp
        GUI/GuiBuilder.cpp
        Controllers/WindowsController.cpp
        Controllers/LinuxController.cpp)

target_link_libraries(
        ColorPicker PRIVATE
        ImguiLib
)

target_include_directories(
        ColorPicker PRIVATE
        ${CMAKE_SOURCE_DIR}/GUI
        ${CMAKE_SOURCE_DIR}/Controllers
)
