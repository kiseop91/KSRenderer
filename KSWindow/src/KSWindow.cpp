#include <KSWindow.h>
#include <Renderer.h>
#include <iostream>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>



MetalSurface::MetalSurface(NS::Window* _pWindow)
{
    CGRect frame = (CGRect){ {0.0, 0.0}, {800.0, 800.0} };

    _pDevice = MTL::CreateSystemDefaultDevice();

    _pMtkView = MTK::View::alloc()->init( frame, _pDevice );
    _pMtkView->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
    _pMtkView->setClearColor( MTL::ClearColor::Make( 0.3, 0.3, 0.3, 1.0 ) );
    

}

MTL::Device* MetalSurface::GetDevice()
{
    return _pDevice;
}

MTL::RenderPassDescriptor* MetalSurface::GetCurrentRenderPassDescriptor()
{
    // 수정해야함.
    MTL::ClearColor clear_color(152.0/255.0, 23.0/255.0, 42.0/255.0, 1.0);
    auto pass_descriptor = MTL::RenderPassDescriptor::alloc()->init();
    auto attachment = pass_descriptor->colorAttachments()->object(0);
    attachment->setClearColor(clear_color);
    attachment->setLoadAction(MTL::LoadActionClear);
    attachment->setTexture(GetCurrentDrawable()->texture());

    return pass_descriptor;
}

CA::MetalDrawable* MetalSurface::GetCurrentDrawable()
{
    return _pMtkView->currentDrawable();
}