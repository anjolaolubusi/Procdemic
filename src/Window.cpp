#include "Window.h"


//Parameterized constructor
Window::Window(int width, int height, const char* title)
{
    //Initalizes glfw
    if(!glfwInit()){
        printf("Failed to initalize GLFW");
    }
    
    //Defines how errors are handled
    glfwSetErrorCallback(ErrorCallback);
    
    //Sets up Window class
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    this->title = title;

    //Check if window is probably defined
    if(!this->window)
    {
        printf("Failed to initalize window");
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
        printf("Failed to initialize GLAD");
        glfwTerminate();
    }
    
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(window, Resize);

}

//Checks if window is running
bool Window::isRunning(){
    return !glfwWindowShouldClose(this->window);
}

//Closes all glfw process
void Window::CloseAllGLFW(){
    glfwTerminate();
    printf("GLFW terminated");

}

//Error handeller
void Window::ErrorCallback(int error, const char* description){
    printf("Error: %s\n", description);
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

void Window::UpdateSysStats(double frametime, double fps, double ram, double cpu)
{
    std::string new_title = this->title;
    new_title += " Frametime: " + std::to_string(frametime) + " FPS: " + std::to_string(fps);
    glfwSetWindowTitle(this->window, new_title.c_str());
}

Window::~Window()
{
    //dtor
}
