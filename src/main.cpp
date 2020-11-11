#include <iostream>
#include "Window.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define FPS 60

void Input(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

int main()
{
Window screen(800, 600, "Test");
glfwSetKeyCallback(screen.window, Input);
double lastTime = glfwGetTime();
double nowTime = 0;
double deltaTime = 0;
while(screen.isRunning()){
    nowTime = glfwGetTime();
    deltaTime = nowTime - lastTime;
    if (1/deltaTime < FPS) {
        screen.UpdateSysStats(deltaTime, 1 / deltaTime, 0, 0);
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        screen.Update();
        lastTime = glfwGetTime();
    }else{
#ifdef _WIN32
        Sleep(deltaTime - 1 / FPS);
#else
        usleep(deltaTime - 1 / FPS);
#endif
    }
}

screen.CloseAllGLFW();

}

