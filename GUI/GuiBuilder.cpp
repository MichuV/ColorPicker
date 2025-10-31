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
    window_flags = 0;
    xScale = 1;
    yScale = 1;
}

void GuiBuilder::SetScales() {
    glfwGetWindowContentScale(window, &xScale, &yScale);
    if (xScale < 1.0f) xScale = 1.0f;
    if (yScale < 1.0f) yScale = 1.0f;

}

void GuiBuilder::imguiInit() {
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");
    ImGuiStyle& style = ImGui::GetStyle();
    style.ScaleAllSizes(xScale);
    window_flags = ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize;
    io.FontGlobalScale = xScale;
}

void GuiBuilder::CreateMainView() const {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
    ImGui::Begin(title.c_str(), nullptr, window_flags);

    if (ImGui::BeginTable("view", 2, ImGuiTableFlags_SizingStretchProp | ImGuiTableFlags_BordersInnerV,
            ImVec2(ImGui::GetIO().DisplaySize))) {
        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        if (ImGui::Button("Pick a color")) {

        }
        ImGui::TableNextColumn();

        if (ImGui::BeginTable("rightView", 2, ImGuiTableFlags_SizingFixedFit)) {
            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text(hexColor.c_str());
            ImGui::TableNextColumn();
            if (ImGui::Button("Copy HEX")) {

            }

            ImGui::TableNextRow();
            ImGui::TableNextColumn();
            ImGui::Text(rgbColor.c_str());
            ImGui::TableNextColumn();
            if (ImGui::Button("Copy RGB")) {

            }
            ImGui::EndTable();
        }
        ImGui::EndTable();
    }

    ImGui::End();
}

void GuiBuilder::RenderFrame() const {
    ImGui::Render();
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
    SetScales();

    glfwMakeContextCurrent(window);
    glfwSetWindowSize(window, static_cast<int>(width * xScale), static_cast<int>(height * yScale));
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

