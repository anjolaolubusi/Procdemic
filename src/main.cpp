#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

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
#define _USE_MATH_DEFINES
#include <math.h>
#include "Objects.h"
#include "ProcGen.h"


#define FPS 60
Logger logger; //Logs all infomation to console and file
Window screen(800, 600, "Test", &logger); //Window objecy
Camera cam; //Camera object

//Handles key inputs for non-Game stuff like pausing, exiting
//TODO: Possible need for case and switch
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

    if(key== GLFW_KEY_E && action == GLFW_PRESS){
        if(screen.isWireframe){
            glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
            screen.isWireframe = !screen.isWireframe;
        }else{
            glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
            screen.isWireframe = !screen.isWireframe;
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
        double lastTime = glfwGetTime(); //Gets time for last frame
        double nowTime, deltaTime = 0; //Sets the variables for the time of current frame and the time between the current frame and last frame
        VertexManager vMan; //Vertex Manager
        ProcGen procGen; //Creates the plane object that would represent our island

        glm::ivec3 grad3[] = {glm::ivec3(1,1,0), glm::ivec3(-1,1,0), glm::ivec3(1,-1,0), glm::ivec3(-1,-1,0),
                              glm::ivec3(1,0,1), glm::ivec3(-1,0,1), glm::ivec3(1,0,-1), glm::ivec3(-1,0,-1),
                              glm::ivec3(0,1,1), glm::ivec3(0,-1,1), glm::ivec3(0,1,-1), glm::ivec3(0,-1,-1)};

        int p[] = {151,160,137,91,90,15,
  131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
  190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
  88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
  77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
  102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
  135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
  5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
  223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
  129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
  251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
  49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
  138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180};

        int perm[512];

        for(int i = 0; i < 512; i++){
            perm[i] = p[i & 255];
        }

        procGen.xNum = 255; //Number of squares on the x-axis for our plane
        procGen.zNum = 255; //Number of squares on the y-axis for our plane
        procGen.AddTriangles(vMan); //Island vertex to vertex Manager
        WorldObjectManager WOM(&logger); //Struct containing all the objects that obey the rules of the world
        PointLightManager POM(&logger); //Struct containing all the point light objects
        SpotLightManager SOM(&logger); //Struct containing all the spot light objects
        DirectionalLightManager DOM(&logger); //Struct containing all the directional light objects
        TextureManager textureManager(&logger); //Struct contains all the textures
        textureManager.AddTexture("default.jpg"); //Adds a texture
        textureManager.AddTexture("container.jpg");
        textureManager.AddTexture("container2.gDiff");
        textureManager.AddTexture("container2_specular.png");
        textureManager.AddTexture("ground-texture.png");
        vMan.SetIncides(); //Sets the incides
        WOM.Add(vMan, vMan.total_num, vMan.indices.data(), vMan.indices.size(), "ground-texture.png", "container2_specular.png", glm::vec3(1, 1, 1), glm::vec3(0, -1, -6),&logger); //Adds plane object

        //POM.Add(glm::vec3(0, -1, -6), glm::vec3(1, 1, 1), glm::vec3(0.6f, 0.6f, 0.6f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.7f, 0.7f, 0.7f), 1.0f, 0.04f, 0.006f);
        DOM.Add(glm::vec3(0, 1, 0), glm::vec3(0.5, 0.5, 0.5), glm::vec3(0.6, 0.6f, 0.6f), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(0.3f, 0.3f, 0.3f), true); //Adds Directional Light
        Shader currShader("light-test", &logger); //Adds shader for the object
        //SOM.Add(cam.cameraPos, cam.cameraFront, glm::cos(glm::radians(12.5f)), glm::vec3(1, 1, 1), glm::vec3(0.3f, 0.3f, 0.3f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.5f, 0.5f, 0.5f), 1.0f, 0.7, 1.8f, true); //Add spotlight
        Shader basicShader("basic", &logger); //Add basic shader for the light object

        WOM.trans_list.back().scale = glm::vec3(2, 1, 2);
        float u_scale = 0.462f;
        bool showHeight = true;

    const char* glsl_version = "#version 330";
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(screen.window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

        logger.Log("Running Program");
        while (screen.isRunning()) {
            glfwPollEvents(); //Gathers events i.e Keyboard presses, exiting window
            nowTime = glfwGetTime(); //Gets the current time
            deltaTime = nowTime - lastTime; //Calculates the time between the currrent frame and the last frame


            if (1 / deltaTime < FPS) { //Checks if the FPS is lower than the max
                screen.UpdateSysStats(deltaTime, 1 / deltaTime, cam.cameraPos.x, cam.cameraPos.y, cam.cameraPos.z); //Updates the title
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT| GL_STENCIL_BUFFER_BIT); //Allows depth
                glClearColor(0.5f, 0.5f, 0.5f, 1.0f); //Sets the background colour to blue


                if (!screen.isPaused) { //If the screen is not paused
                    cam.MoveCamera(screen); //Moves the camera according to the user's movement
                    cam.RotateCamera(screen); //Rotates the camera according to the user's movement
                }

                //SOM.pos_list.back() = cam.cameraPos; //Updates the spotlight postion
                //SOM.direction_list.back() = cam.cameraFront; //Updates the spotlight's direction

                WOM.Update(); //Updates the world's update
                WOM.Draw(&currShader, cam, textureManager, DOM, POM, SOM, u_scale, showHeight, grad3, perm); //Draws the World Objects to screen

                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplGlfw_NewFrame();
                ImGui::NewFrame();

                ImGui::Begin("Procedual Generation Options");
                ImGui::SliderFloat("Scale", &u_scale, 0.0f, 1.0f);
                ImGui::Checkbox("Show Height", &showHeight);
                std::string fpsString = "FPS: " + std::to_string(1/deltaTime);
                ImGui::Text(fpsString.c_str());
                ImGui::End();

                ImGui::Render();
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

                screen.Update(); //Updates the screen
                lastTime = glfwGetTime(); //Gets the time for the last frame
            } else {
#ifdef _WIN32
                Sleep(deltaTime - 1 / FPS); //Sleeps if on windows
#else
                usleep(deltaTime - 1 / FPS); //Sleeps if on mac
#endif
            }
        }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

        screen.CloseAllGLFW(); //Closes window and deletes window/GLFW from memory
    }catch(const char* msg){
        return -1;
    }

    return 0;
}
