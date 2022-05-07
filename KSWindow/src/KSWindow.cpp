#include <KSWindow.h>
#include <Renderer.h>
#include <iostream>
void KSWindow::TestWindow()
{
    std::cout << "Create Test Window! \n";
    Renderer rd;
    rd.Draw();
}