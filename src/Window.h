#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include "Logger.h"


class Window
{
    public:
        GLFWwindow* window; //GLFWwindow object, (used to step up window)
        Window(int width, int height, const char* title, Logger* logger); //Constructor
        bool isRunning(); //Checks if window is running
        void CloseAllGLFW(); //Closes all glfw process
        void ErrorCallback(int error, const char* description); //Error handeller
        void Update(); //Updates screen
        static void Resize(GLFWwindow* window, int width, int height); //Resizes window
        void UpdateSysStats(double frametime, double fps);
        virtual ~Window();

        const char* title;
        Logger* logger;

    protected:

    private:
};

#endif // WINDOW_H
