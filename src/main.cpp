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

#define FPS 60
Logger logger;
Camera cam;
Window screen(800, 600, "Test", &logger);

//Test

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
        Vertex vert[] = {
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)), //0
        Vertex(glm::vec3(1.0f, 1.0f, -1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, -1.0f)), //3

        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)), //4
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(-1.0f, 0.0f, 0.0f)), //7

        Vertex(glm::vec3(1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)), //8
        Vertex(glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)) ,
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f)), //11

        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)), //12
        Vertex(glm::vec3(1.0f, 1.0f, 1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 1.0f)), //15

        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)), //16
        Vertex(glm::vec3(1.0f, 1.0f, -1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)),
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, 1.0f, 0.0f)), //19

        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)), //20
        Vertex(glm::vec3(1.0f, -1.0f, -1.0), glm::vec2(1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f), glm::vec3(0.0f, -1.0f, 0.0f)), //23
        };
        unsigned int indices[] = 
        {0, 2, 3, 
         0, 1, 3, 

        4, 6, 7,
        4, 5, 7,

        8, 10, 11,
        8, 9, 11,

        12, 14, 15,
        12, 13, 15,

        16, 18, 19,
        16, 17, 19,

        20, 22, 23,
        20, 21, 23,
         };
        LightSource lightSource(vert, sizeof(vert) / sizeof(vert[0]), indices, sizeof(indices) / sizeof(indices[0]), "default.jpg", &logger);
        WorldObject LightReciever(vert, sizeof(vert) / sizeof(vert[0]), indices, sizeof(indices) / sizeof(indices[0]), "container.jpg", &logger);
        Shader LS("lightsource", &logger);
        Shader LR("basic", &logger);
        float counter = 0.0f;

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

                    //trans.GetRot()->y = sin(glfwGetTime() * (M_PI / 180)) * 100;
                    LightReciever.transform.GetPos()->z = -2;
                    LightReciever.transform.GetPos()->x = 10;

                    lightSource.transform.GetPos()->z = -2 + sin(glfwGetTime() * (M_PI / 180) * 100) * 10;
                    lightSource.transform.GetPos()->x = 10 + cos(glfwGetTime() * (M_PI / 180) * 100) * 10;

                    LR.Use();
                    LR.Update(LightReciever.transform, cam);
                    LightReciever.Draw(LR.shaderProgram);

                    LS.Use();
                    LS.Update(lightSource.transform, cam);
                    lightSource.Draw(LS.shaderProgram);
                    screen.Update();

                    counter++;
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
