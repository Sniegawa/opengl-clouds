#include "app.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <iostream>
#include <memory>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

App::App()
{
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

    glfwSetInputMode(m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(!gladLoadGL((GLADloadfunc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return; // TODO: same as glfw error
    }

    
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glfwSetWindowUserPointer(m_Window, this);
    glfwSetFramebufferSizeCallback(m_Window, &App::framebufferResizeCallback);

    m_Renderer = std::make_unique<Renderer::Renderer>(WINDOW_WIDTH,WINDOW_HEIGHT);

    m_Camera.SetFov(75);
    m_Camera.SetPosition(glm::vec3(0.0f));
    m_Camera.SetAspectRatio(float(WINDOW_WIDTH) / float(WINDOW_HEIGHT));
}

App::~App()
{
    glfwDestroyWindow(m_Window);
    glfwTerminate();
}

void App::Run()
{
    float lastTime = glfwGetTime();
    float currentTime = lastTime;
    while(!glfwWindowShouldClose(m_Window))
    {
        glfwPollEvents();

        currentTime = glfwGetTime();
        float dt = currentTime - lastTime;
        lastTime = currentTime;

        m_Camera.ProcessInputs(m_Window, dt);


        m_Renderer->Render(m_Camera);


        glfwSwapBuffers(m_Window);



    }
}



void App::framebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    auto* app = static_cast<App*>(glfwGetWindowUserPointer(window));

    app->m_Renderer->OnResize(width, height);

    app->m_Camera.SetAspectRatio(float(width)/float(height));
}
