#pragma once

#include <memory>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "renderer/Renderer.hpp"


class App {
public:
    App();
    ~App();


    void Run();

private:
    static void framebufferResizeCallback(GLFWwindow* window, int width, int height);

private:
    GLFWwindow* m_Window;

    std::unique_ptr<Renderer::Renderer> m_Renderer;
};
