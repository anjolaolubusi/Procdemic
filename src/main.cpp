#include <iostream>
#include "Logger.h"
#include "Window.h"
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"
#include "Camera.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Objects.h"

#define FPS 120
Logger logger;
Camera cam;
Window screen(800, 600, "Test", &logger);

void Input(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        screen.isPaused = !screen.isPaused;
        glfwGetCursorPos(window, &cam.oldX, &cam.oldY);
        if (screen.isPaused) {
            screen.hasBeenPaused = true;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        }
        else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

}

//Error handeller
void ErrorCallback(int error, const char* description) {
    throw description;
}


int main()
{
    try {
        glfwSetKeyCallback(screen.window, Input);
        glfwSetErrorCallback(ErrorCallback);
        double lastTime = glfwGetTime();
        double nowTime, deltaTime = 0;
        VertexManager vMan;
        vMan.Add(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f));
        vMan.Add(glm::vec3(-1.0f, 1.0f, 1.0), glm::vec2(0.0f, 1.0f));
        vMan.Add(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 0.0f));
        vMan.Add(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 0.0f));
        WorldObjectManager WOM(&logger);
        unsigned int indices[] = {2, 1, 0 };
        WOM.Add(vMan, vMan.total_num, indices, sizeof(indices) / sizeof(indices[0]), "container.jpg", &logger);
        Shader currShader("lightsource", &logger);
        while (screen.isRunning()) {
            glfwPollEvents();
            nowTime = glfwGetTime();
            deltaTime = nowTime - lastTime;
            if (1 / deltaTime < FPS) {
                screen.UpdateSysStats(deltaTime, 1 / deltaTime);
                if (!screen.isPaused) {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glClearColor(0.4f, 0.2f, 0.6f, 1.0f);

                    cam.MoveCamera(screen);
                    cam.RotateCamera(screen);

                    WOM.Update();
                    WOM.Draw(&currShader, cam);                    
                    screen.Update();
                }
                lastTime = glfwGetTime();
            }
            else {
#ifdef _WIN32
                Sleep(deltaTime - 1 / FPS);
#else
                usleep(deltaTime - 1 / FPS);
#endif
            }
        }

        screen.CloseAllGLFW();
    }catch(const char* msg){

    }

    return 0;
}
