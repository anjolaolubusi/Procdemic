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

#define FPS 60
Logger logger;

void Input(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

//Error handeller
void ErrorCallback(int error, const char* description) {
    throw description;
}


int main()
{
    try {
        Window screen(1280, 720, "Test", &logger);
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
        Texture tt("container.jpg", &logger);
        Mesh mm(vert, sizeof(vert)/sizeof(vert[0]), &logger);
        Transform trans;
        float counter = 0.0f;

        while (screen.isRunning()) {
            nowTime = glfwGetTime();
            deltaTime = nowTime - lastTime;
            if (1 / deltaTime < FPS) {
                screen.UpdateSysStats(deltaTime, 1 / deltaTime);
                glClear(GL_COLOR_BUFFER_BIT);
                glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
                
                trans.GetPos()->x = sinf(counter);
                trans.GetPos()->y = cosf(counter);

                ss.Update(trans);
                mm.Draw(ss.shaderProgram);
                tt.Draw(0);
                
                counter += 0.1f;

                screen.Update();
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
