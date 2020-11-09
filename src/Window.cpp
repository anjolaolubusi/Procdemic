#include "Window.h"
#include <iostream>


//Parameterized constructor
Window::Window(int width, int height, std::string title)
{
    //Initalizes glfw
    if(!glfwInit()){
        std::cout << "Failed to initalize GLFW" << std::endl;
    }
    
    //Defines how errors are handled
    glfwSetErrorCallback(ErrorCallback);
    
    //Sets up Window class
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    
    //Check if window is probably defined
    if(!this->window)
    {
        std::cout << "Failed to initalize window" << std::endl;
        glfwTerminate();
    }
    
    //Defines OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#if __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    //Sets current context to this window
    glfwMakeContextCurrent(this->window);
    
    //Imports glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
    }
    
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, Resize);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

}

//Checks if window is running
bool Window::isRunning(){
    return !glfwWindowShouldClose(this->window);
}

//Closes all glfw process
void Window::CloseAllGLFW(){
    glfwTerminate();
    std::cout << "GLFW terminated" << std::endl;

}

//Error handeller
void Window::ErrorCallback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description);
}


//Updates screen
void Window::Update(){
    glfwSwapBuffers(this->window);
    glfwSwapInterval(1);
    glfwPollEvents();
}

void Window::Resize(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

Window::~Window()
{
    //dtor
}
