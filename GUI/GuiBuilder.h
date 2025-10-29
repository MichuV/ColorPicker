#ifndef GUIBUILDER_H
#define GUIBUILDER_H

#include <iostream>
#include "GLFW/glfw3.h"

using namespace std;

class GuiBuilder {
private:
    int width, height;
    string title, hexColor, rgbColor;
    GLFWwindow* window;

    void imguiInit() const;
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
