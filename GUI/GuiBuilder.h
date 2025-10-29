#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <imgui.h>
#include <iostream>
#include "GLFW/glfw3.h"

using namespace std;

class GuiBuilder {
private:
    int width, height;
    string title, hexColor, rgbColor;
    GLFWwindow* window;
    ImGuiWindowFlags window_flags;

    void imguiInit();
    void CreateMainView() const;
    void RenderFrame() const;
    void ShutdownGui();

public:
    GuiBuilder(int width, int height);
    void WindowInit();
    void RunGui();
    ~GuiBuilder();
};

#endif //GUIBUILDER_H
