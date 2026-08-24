#include "Renderer.hpp"
#include "RenderContext.hpp"

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


        m_NoisePass.execute(m_Context);
    }


    Renderer::~Renderer()
    {

    }

    void Renderer::Render(const Camera& camera)
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
        glClearColor(0.2f, 0.2f, 0.8f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT); 


        m_CloudPass.execute(m_Context);

        m_FSQpass.execute(m_Context);
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
