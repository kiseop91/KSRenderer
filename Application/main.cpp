
#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION
#include <KSWindow.h>
#include <Renderer.h>
#include <iostream>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_metal.h"

#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>



int main( int argc, char* argv[] )
{
    MTL::Device* dvice = MTL::CreateSystemDefaultDevice();
    dvice->newCommandQueue();
    CA::MetalLayer* layer;
    
    MTK::View* view = MTK::View::alloc();
    

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();

    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800,800, "test", NULL,NULL);
    NS::Window* _pWindow = (NS::Window*)glfwGetCocoaWindow(window);
    
    MetalSurface surface(_pWindow);
    Renderer renderer(surface.GetDevice());
   
    ImGui_ImplGlfw_InitForOther(window, true);
    ImGui_ImplMetal_Init(surface.GetDevice());

    auto cBuffer = renderer._pCommandQueue->commandBuffer();
    auto cEncoder = cBuffer->renderCommandEncoder(surface.GetCurrentRenderPassDescriptor());

    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents(); 

        ImGui_ImplMetal_NewFrame(surface.GetCurrentRenderPassDescriptor());
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        
       renderer.SetRenderPassDescriptor(surface.GetCurrentRenderPassDescriptor());
       renderer.draw(surface.GetCurrentDrawable());
       
       glfwSwapBuffers(window);
      
    }
    return 0;
}