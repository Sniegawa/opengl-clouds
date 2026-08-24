#pragma once

#include "RenderPass.hpp"

#include "../RenderContext.hpp"
#include "../Shader.hpp"
#include "../ShaderResources.hpp"

namespace Renderer
{
    
    class FSQPass : public RenderPass
    {
        public:
            FSQPass(const Texture& inputTexture);

            ~FSQPass();

            void execute(RenderContext& context) override;
            
            void onImGui(RenderContext& context) override;

        private:
            Shader m_Shader;
            ShaderResources m_Resources;

            unsigned int m_VAO = 0; // needed because of opengl
    };

}
