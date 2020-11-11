#include <iostream>
#include "Window.h"

void Input(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
Window screen(800, 600, "Test");
glfwSetKeyCallback(screen.window, Input);

double beginTime = 0;
double lastTime = 0;
double FPS = 0;
while(screen.isRunning()){
    FPS = 1 / (lastTime - beginTime);
    beginTime = glfwGetTime();
    glClear(GL_COLOR_BUFFER_BIT);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    screen.Update();
    lastTime = glfwGetTime();
}

screen.CloseAllGLFW();

}

