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
    CGRect frame = (CGRect){ {100.0, 100.0}, {512.0, 512.0} };
    GLFWwindow* window = glfwCreateWindow(512, 512, "KSRenderer", NULL,NULL);
    auto nswindow = (NS::Window*)glfwGetCocoaWindow(window);
     
    auto _pDevice = MTL::CreateSystemDefaultDevice();

    auto _pMtkView = MTK::View::alloc()->init( frame, _pDevice );
    _pMtkView->setColorPixelFormat( MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB );
    _pMtkView->setClearColor( MTL::ClearColor::Make( 0.3, 0.3, 0.3, 1.0 ) );

    nswindow->setContentView( _pMtkView );
    nswindow->makeKeyAndOrderFront( nullptr );  
    
    Renderer renderer(_pDevice);

int i = 0;
    while(!glfwWindowShouldClose(window))
    {
        int width, height;
        glfwGetFramebufferSize(window, &width, &height);
        std::cout <<  i++ <<" : "<< width << " , " << height << std::endl;

        renderer.draw(_pMtkView);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}