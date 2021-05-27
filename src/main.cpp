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
#include "ProcGen.h"

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
        ProcGen procGen;
        procGen.xNum = 20;
        procGen.zNum = 20;
        procGen.AddTriangles(vMan);
        WorldObjectManager WOM(&logger);
        LightObjectManager LOM(&logger);
        TextureManager textureManager(&logger);
        textureManager.AddTexture("default.jpg");
        textureManager.AddTexture("container.jpg");
        vMan.SetIncides();
        LOM.Add(vMan, vMan.total_num, vMan.indices.data(), vMan.indices.size(), "default.jpg", &logger);
        WOM.Add(vMan, vMan.total_num, vMan.indices.data(), vMan.indices.size(), "container.jpg", &logger);
        Shader currShader("light-test", &logger);
        Shader basicShader("basic", &logger);
        while (screen.isRunning()) {
            glfwPollEvents();
            nowTime = glfwGetTime();
            deltaTime = nowTime - lastTime;
            if (1 / deltaTime < FPS) {
                screen.UpdateSysStats(deltaTime, 1 / deltaTime, cam.cameraPos.x, cam.cameraPos.y, cam.cameraPos.z);
                if (!screen.isPaused) {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

                    cam.MoveCamera(screen);
                    cam.RotateCamera(screen);

                    WOM.Update();
                    LOM.Update();
                    LOM.Draw(&basicShader, cam, textureManager);
                    WOM.Draw(&currShader, cam, textureManager, LOM.trans_list.back());
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
        return -1;
    }

    return 0;
}
