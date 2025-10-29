#include <iostream>
#include "GuiBuilder.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "GLFW/glfw3.h"

GuiBuilder::GuiBuilder(int width, int height) : width(width), height(height) {
    title = "Color Picker";
    hexColor = "#XXXXXX";
    rgbColor = "rgb(XXX, XXX, XXX)";
    window = nullptr;
}

void GuiBuilder::imguiInit() const {
    ImGui::CreateContext();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
}

void GuiBuilder::CreateMainView() const {
    ImGui::Begin(title.c_str());
    if (ImGui::Button("Test button")) {}
    ImGui::End();
}

void GuiBuilder::RenderFrame() const {
    ImGui::Render();
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    glViewport(0, 0, bufferWidth, bufferHeight);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    glfwSwapBuffers(window);
}

void GuiBuilder::ShutdownGui() {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    window = nullptr;
}

void GuiBuilder::WindowInit() {
    if (!glfwInit()) return;

    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    imguiInit();
}

void GuiBuilder::RunGui() {
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        CreateMainView();
        RenderFrame();
    }

    ShutdownGui();
}

GuiBuilder::~GuiBuilder() {
    if (window)
        ShutdownGui();
}

