#pragma once

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <MetalKit/MetalKit.hpp>
class Renderer;
class MetalSurface 
{
public:
    MetalSurface(NS::Window* _pWindow);
    CA::MetalDrawable* GetCurrentDrawable();
    MTL::Device* GetDevice();
    MTL::RenderPassDescriptor* GetCurrentRenderPassDescriptor();

private:
    MTK::View* _pMtkView;
    MTL::Device* _pDevice;
};