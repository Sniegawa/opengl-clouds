#include "Renderer.hpp"
#include "RenderContext.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <glad/gl.h>
#include <iostream>

namespace Renderer
{

    Renderer::Renderer(uint32_t width, uint32_t height)
        :
        m_Context(width,height),
        m_NoisePass(m_Context),
        m_CloudPass(m_Context),
        m_FSQpass(m_Context.outputTexture)
    {
        CameraData DefaultCameraData;
        m_Context.cameraUniformBuffer.setData(&DefaultCameraData, sizeof(CameraData));
       
        FrameData DefaultFrameData;
        m_Context.frameUniformBuffer.setData(&DefaultFrameData, sizeof(FrameData));

        CloudData DefaultCloudData;
        m_Context.cloudSettingsBuffer.setData(&DefaultCloudData, sizeof(CloudData));

        NoiseData DefaultNoiseData;
        DefaultNoiseData = MakeDefaultNoiseData();
        m_Context.NoiseSettingsBuffer.setData(&DefaultNoiseData, sizeof(NoiseData));

    }


    Renderer::~Renderer()
    {

    }

    void Renderer::Render(const Camera& camera, float dt)
    {
        // Update Camera data context
        {
            CameraData data;
            data.Position = camera.GetPosition();
            data.InverseViewProjection = camera.GetInverseViewProjection();
            data.Projection = camera.GetProjectionMatrix();
            data.View = camera.GetViewMatrix();

            m_Context.cameraUniformBuffer.update(&data, sizeof(CameraData));
        }

        m_FrameData.time += dt;
        m_Context.frameUniformBuffer.update(&m_FrameData, sizeof(FrameData));


        glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT); 

        if(m_Context.RegenNoise)
        {
            m_Context.RegenNoise = false;
            m_NoisePass.execute(m_Context);
        }

        m_CloudPass.execute(m_Context);

        m_FSQpass.execute(m_Context);
    }

    void ShowPerfWindow(float deltaTime) // deltaTime in seconds, pass in each frame
    {
    static float fpsTimer = 0.0f;
    static int frameCount = 0;
    static float avgFPS = 0.0f;
    static float ms = 16.67f;

    fpsTimer += deltaTime;
    frameCount++;

    if (fpsTimer >= 1.0f)
    {
        avgFPS = frameCount / fpsTimer;
        ms = 1000.0f / avgFPS;
        frameCount = 0;
        fpsTimer = 0.0f;
    }

    


    ImGui::Begin("Performance");
    ImGui::Text("Frame time: %.3f ms", ms);
    ImGui::Text("Avg FPS: %.1f", avgFPS);
    ImGui::End();
    }


    void Renderer::RenderImGui(float dt)
    {
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();

        ImGui::NewFrame();

        ShowPerfWindow(dt);

        m_NoisePass.onImGui(m_Context);

        m_CloudPass.onImGui(m_Context);

        ImGui::EndFrame();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }


    void Renderer::OnResize(uint32_t width, uint32_t height)
    {
        if(width == 0 || height == 0)
            return; // minimised

        if(width == m_Context.width && height == m_Context.height)
            return;

        std::cout << "Resizing renderer to : " << width << "x" << height << std::endl;

        m_Context.width = width;
        m_Context.height = height;


        m_Context.outputTexture.Resize(width, height);

        glViewport(0,0,width,height); // TODO: Move it elsewhere and keep glad out of this file
    }
}
