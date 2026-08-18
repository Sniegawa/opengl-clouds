#include "app.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

App::App()
{
    std::cout<<"TEST"<<std::endl;
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_Window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Clouds", NULL, NULL);

    if(m_Window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return; // TODO: crash whole program
    }

    glfwMakeContextCurrent(m_Window);

    //glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return; // TODO: same as glfw error
    }

    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

}

App::~App()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void App::Run()
{
    while(!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();

        

        glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT); 

        glfwSwapBuffers(m_Window);
    }
}
