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
#include "Object.h"

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
        Shader ss("basic", &logger);
        Vertex vert[] = {
        Vertex(glm::vec3(-0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f)),
        Vertex(glm::vec3(0.0f, 0.5f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.5f, 1.0f)),
        };
        Texture tt(&logger, "container.jpg");
        Mesh mm(vert, sizeof(vert)/sizeof(vert[0]), &logger);
        Object obj(Mesh(vert, sizeof(vert) / sizeof(vert[0]), &logger), Texture(&logger, "container.jpg"));
        Transform trans;
        float counter = 0.0f;

        while (screen.isRunning()) {
            glfwPollEvents();
            nowTime = glfwGetTime();
            deltaTime = nowTime - lastTime;
            if (1 / deltaTime < FPS) {
                screen.UpdateSysStats(deltaTime, 1 / deltaTime);
                if (!screen.isPaused) {
                    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

                    cam.MoveCamera(screen);
                    cam.RotateCamera(screen);

                    trans.GetRot()->y = sin(counter);
                    trans.GetPos()->z = -2;

                    obj.transform.GetPos()->z = -2;
                    obj.transform.GetPos()->x = 1;

                    for (int i = 0; i < 2; i++) {
                        if (i == 0) {
                            ss.Update(trans, cam);
                            mm.Draw(ss.shaderProgram);
                        }
                        else {
                            ss.Update(obj.transform, cam);
                            obj.Draw(ss.shaderProgram);
                        }
                    }
                    tt.Draw(0);

                    counter += 0.1f;

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
