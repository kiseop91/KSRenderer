
#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>

class Renderer
{
    public:
        Renderer( MTL::Device* pDevice );
        void SetRenderPassDescriptor (MTL::RenderPassDescriptor* pRpd);
        ~Renderer();
        void draw( CA::MetalDrawable* _renderTarget );

    private:
        void buildShaders();
        void buildBuffers();
    private:
        MTL::Device* _pDevice;
        MTL::CommandQueue* _pCommandQueue;
        MTL::RenderPipelineState* _pPSO;
        MTL::RenderPassDescriptor* _pRpd;
        MTL::Buffer* _pVertexPositionsBuffer;
        MTL::Buffer* _pVertexColorsBuffer;
        MTL::Buffer* _pIndexBuffer;
        MTL::Buffer* _pRotBuffer;
};