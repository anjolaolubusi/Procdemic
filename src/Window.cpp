#include "Window.h"
#include <iostream>


Window::Window(int width, int height, std::string title)
{
    if(!glfwInit()){
        std::cout << "Failed to initalize GLFW" << std::endl;
    }
    glfwSetErrorCallback(ErrorCallback);
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if(!this->window)
    {
        std::cout << "Failed to initalize window" << std::endl;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwMakeContextCurrent(this->window);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
    glfwSetKeyCallback(window, key_callback);
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
}

bool Window::isRunning(){
    return !glfwWindowShouldClose(this->window);
}

void Window::CloseWindow(){
    glfwTerminate();
    std::cout << "GLFW terminated" << std::endl;

}

void Window::ErrorCallback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void Window::Update(){
    glfwSwapBuffers(this->window);
    glfwSwapInterval(1);
    glfwPollEvents();
}

Window::~Window()
{
    //dtor
}
