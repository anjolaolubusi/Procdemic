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
        Shader LS("basic", "lightsource", &logger);
        Shader LR("basic", &logger);
        Vertex vert[] = {
        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(1.0f, 1.0f, -1.0), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, -1.0f), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, -1.0f), glm::vec2(1.0f, 1.0f)),

        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(-1.0f, -1.0f, 1.0f), glm::vec2(1.0f, 1.0f)),

        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(1.0f, -1.0f, 1.0f), glm::vec2(0.0f, 1.0f)),

        Vertex(glm::vec3(-1.0f, 1.0f, -1.0f), glm::vec2(0.0f, 1.0f)),
        Vertex(glm::vec3(1.0f, 1.0f, -1.0), glm::vec2(1.0f, 1.0f)),
        Vertex(glm::vec3(-1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),

        };
        unsigned int indices[] = 
        {0, 2, 3, 
         0, 1, 3, 
         
         0, 4, 2,
         4, 2, 5,
        
         1, 6, 3,
         3, 7, 6,

         4, 5, 7,
         4, 6, 7,

         8, 9, 10,
         9, 11, 10
         };
        Texture tt(&logger, "container.jpg");
        Texture tt2(&logger);
        LightSource lightSource(vert, sizeof(vert) / sizeof(vert[0]), indices, sizeof(indices) / sizeof(indices[0]), tt, &logger);
        WorldObject LightReciever(vert, sizeof(vert) / sizeof(vert[0]), indices, sizeof(indices) / sizeof(indices[0]), tt2, &logger);
        float counter = 0.0f;
        float ambient = 0.5f;
        LightReciever.Light = LightReciever.Light * ambient;

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
                    lightSource.transform.GetPos()->z = -2;
                    lightSource.transform.GetPos()->x = 10;
                    LightReciever.transform.GetPos()->z = -2;
                    LightReciever.transform.GetPos()->x = 15;

                    LS.Update(lightSource.transform, cam);
                    lightSource.Draw(LS.shaderProgram);
                    LR.Update(LightReciever.transform, cam);
                    LightReciever.Draw(LR.shaderProgram);
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
