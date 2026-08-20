#include "TestComputePass.hpp"

namespace Renderer
{
    TestComputePass::TestComputePass(RenderContext& context) 
        :
        m_CompShader("resources/shaders/test.comp")
    {
        m_Width = context.width;
        m_Height = context.height;

        m_Resources.setImage(0, context.TestOutputTexture, ImageAccess::WriteOnly);
    }


    void TestComputePass::execute(RenderContext& context)
    {
        m_CompShader.bind();


        m_Resources.bind();

        m_CompShader.dispatch((context.width + 7) / 8, (context.height + 7) / 8, 1);
    }

}

