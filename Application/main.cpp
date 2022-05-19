#define NS_PRIVATE_IMPLEMENTATION
#define MTL_PRIVATE_IMPLEMENTATION
#define MTK_PRIVATE_IMPLEMENTATION
#define CA_PRIVATE_IMPLEMENTATION

#include <KSWindow.h>
#include <Renderer.h>
#include <iostream>
#include <GLFW/glfw3.h>
#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

int main( int argc, char* argv[] )
{
    glfwInit();
    GLFWwindow* window = glfwCreateWindow(800,800, "test", NULL,NULL);
    NS::Window* _pWindow = (NS::Window*)glfwGetCocoaWindow(window);
    
    MetalSurface surface(_pWindow);
    Renderer renderer(surface.GetDevice());
    
   while(!glfwWindowShouldClose(window))
   {
       renderer.SetRenderPassDescriptor(surface.GetCurrentRenderPassDescriptor());
       renderer.draw(surface.GetCurrentDrawable());
       
       glfwSwapBuffers(window);
       glfwPollEvents();
   }
    return 0;
}