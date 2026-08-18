#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>


class App {
public:
    App();
    ~App();


    void Run();


private:
    GLFWwindow* m_Window;
};
