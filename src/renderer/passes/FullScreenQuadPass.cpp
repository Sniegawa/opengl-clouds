#include "FullScreenQuadPass.hpp"

#include <glad/gl.h>

namespace Renderer
{

    FSQPass::FSQPass(const Texture& inputTexture)
        : m_Shader("resources/shaders/fullscreen.vert","resources/shaders/fullscreen.frag")
    {
        m_Resources.setTexture(0, inputTexture);
        glCreateVertexArrays(1, &m_VAO);
    }

    FSQPass::~FSQPass()
    {
        glDeleteVertexArrays(1, &m_VAO);
    }

    void FSQPass::execute(RenderContext& context)
    {
        m_Shader.bind();

        m_Resources.bind();

        glBindVertexArray(m_VAO);

        glDrawArrays(GL_TRIANGLES,0,3);

        glad_glBindVertexArray(0);
    }

    void FSQPass::onImGui(RenderContext& context) {}

}
