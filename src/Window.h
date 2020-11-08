#ifndef WINDOW_H
#define WINDOW_H
#define GLFW_INCLUDE_NONE
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window
{
    public:
        GLFWwindow* window;
        Window(int width, int height, std::string title);
        bool isRunning();
        void CloseWindow();
        static void ErrorCallback(int error, const char* description);
        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void Update();
        virtual ~Window();

    protected:

    private:
};

#endif // WINDOW_H
