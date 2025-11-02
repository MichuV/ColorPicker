#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <Controller.h>
#include <imgui.h>
#include <string>
#include "GLFW/glfw3.h"

class GuiBuilder {
private:
    int width, height;
    float xScale, yScale;
    std::string title, hexColorStr, rgbColorStr;
    GLFWwindow* window;
    ImGuiWindowFlags window_flags;
    Controller* controller;

    void SetScales();
    void SetStrings();
    void imguiInit();
    void CreateMainView();
    void RenderFrame() const;
    void ShutdownGui();

public:
    GuiBuilder(int width, int height, Controller* controller);
    void WindowInit();
    void RunGui();
    ~GuiBuilder();
};

#endif //GUIBUILDER_H
