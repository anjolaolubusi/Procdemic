#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
    public:
        GLFWwindow* window; //GLFWwindow object, (used to step up window)
        Window(int width, int height, std::string title); //Constructor
        bool isRunning(); //Checks if window is running
        void CloseAllGLFW(); //Closes all glfw process
        static void ErrorCallback(int error, const char* description); //Error handeller
        void Update(); //Updates screen
        static void Resize(GLFWwindow* window, int width, int height); //Resizes window
        virtual ~Window();

    protected:

    private:
};

#endif // WINDOW_H
