#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Logger.h"

struct Window
{
        GLFWwindow* window; //GLFWwindow object, (used to step up window)

        //Constructor
        Window(int width, int height, const char* title, Logger* logger) {
            this->logger = logger;
                //Initalizes glfw
                if (!glfwInit()) {
                    this->logger->Log("Failed to initalize GLFW");
                    throw "Failed to initalize GLFW";
                }

                //Defines OpenGL context
                glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
                glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
                //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    #if __APPLE__
                glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif


                //Sets up Window class
                window = glfwCreateWindow(width, height, title, NULL, NULL);
                this->title = title;

                //Check if window is probably defined
                if (!this->window)
                {
                    glfwTerminate();
                    this->logger->Log("Failed to initalize window");
                    throw "Failed to initalize window";
                }

                //Sets current context to this window
                glfwMakeContextCurrent(this->window);

                //Imports glad
                if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
                {
                    glfwTerminate();
                    this->logger->Log("Failed to initialize GLAD");
                    throw "Failed to initialize GLAD";
                }

                /*if(gladLoadGL() == 0){
                     glfwTerminate();
                    this->logger->Log("Failed to initialize GLAD");
                    throw "Failed to initialize GLAD";
                }*/

                glfwGetFramebufferSize(window, &width, &height);
                glViewport(0, 0, width, height);
                glEnable(GL_DEPTH_TEST);
                glfwSetFramebufferSizeCallback(window, Resize);
                glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }

        //Checks if window is running
        bool isRunning() {
            return !glfwWindowShouldClose(this->window);
        }

        //Closes all glfw process
        void CloseAllGLFW() {
            glfwTerminate();
            this->logger->Log("GLFW terminated");
        }

        //Error handeller
//        void ErrorCallback(int error, const char* description);

        //Updates screen
        void Update() {
            glfwSwapBuffers(this->window);
            glfwSwapInterval(1);
            glfwPollEvents();
        }

        //Resizes window
        static void Resize(GLFWwindow* window, int width, int height) {
            glViewport(0, 0, width, height);
        }

        void UpdateSysStats(double frametime, double fps, float x, float y, float z) {
            double width, height;
            glfwGetCursorPos(this->window, &width, &height);
            std::string new_title = this->title;
            new_title += " Frametime: " + std::to_string(frametime) + " FPS: " + std::to_string(fps)
            + " X: " + std::to_string(x) + " Y: " + std::to_string(y) + " Z: " + std::to_string(z);
            glfwSetWindowTitle(this->window, new_title.c_str());
        }

        ~Window() {
            logger->Log("Destructing Window class");
        }

        const char* title;
        Logger* logger;
        bool isPaused = false;
        bool hasBeenPaused = false;
        bool isWireframe = true;

};

#endif // WINDOW_H
