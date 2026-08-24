#pragma once



namespace Renderer
{
    class RenderContext;
    // RenderPass interface 
    class RenderPass
    {
        public:

        virtual ~RenderPass() = default;

        virtual void execute(RenderContext& context) = 0;

        virtual void onImGui(RenderContext& context) = 0;
    };


}
