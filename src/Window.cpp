#include "Window.h"


//Parameterized constructor
Window::Window(int width, int height, const char* title, Logger* logger){
    this->logger = logger;
    //Initalizes glfw
    if(!glfwInit()){
        this->logger->Log("Failed to initalize GLFW");
        throw "Failed to initalize GLFW";
    }

    //Sets up Window class
    window = glfwCreateWindow(width, height, title, NULL, NULL);
    this->title = title;

    //Check if window is probably defined
    if(!this->window)
    {
        glfwTerminate();
        this->logger->Log("Failed to initalize window");
        throw "Failed to initalize window";
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
        glfwTerminate();
        this->logger->Log("Failed to initialize GLAD");
        throw "Failed to initialize GLAD";
    }

    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);
    glEnable(GL_DEPTH_TEST);
    glfwSetFramebufferSizeCallback(window, Resize);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

//Checks if window is running
bool Window::isRunning(){
    return !glfwWindowShouldClose(this->window);
}

//Closes all glfw process
void Window::CloseAllGLFW(){
    glfwTerminate();
    this->logger->Log("GLFW terminated");

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

void Window::UpdateSysStats(double frametime, double fps)
{
    std::string new_title = this->title;
    new_title += " Frametime: " + std::to_string(frametime) + " FPS: " + std::to_string(fps);
    glfwSetWindowTitle(this->window, new_title.c_str());
}

Window::~Window()
{
    logger->Log("Destructing Window class");
}
