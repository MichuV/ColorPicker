#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <Controller.h>
#include <imgui.h>
#include <iostream>
#include "GLFW/glfw3.h"

using namespace std;

class GuiBuilder {
private:
    int width, height;
    float xScale, yScale;
    string title, hexColorStr, rgbColorStr;
    GLFWwindow* window;
    ImGuiWindowFlags window_flags;
    Controller* controller;

    void SetScales();
    void imguiInit();
    void CreateMainView() const;
    void RenderFrame() const;
    void ShutdownGui();

public:
    GuiBuilder(int width, int height, Controller* controller);
    void WindowInit();
    void RunGui();
    ~GuiBuilder();
};

#endif //GUIBUILDER_H
