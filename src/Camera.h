#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <GLFW/glfw3.h>
#include "Window.h"

struct Camera
{
    public:

        glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, -6.0f); //Camera's current position
        glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f); //Camera's forward facing direction
        glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //Camera's Up vector

        float cameraSpeed = 0.05f;
        float sensitivity = 1.0f;

        //Moves the camera
        void MoveCamera(Window &window) {
            cameraPos += cameraSpeed * ((glfwGetKey(window.window, GLFW_KEY_W) == GLFW_PRESS) - (glfwGetKey(window.window, GLFW_KEY_S) == GLFW_PRESS)) * cameraFront;
            cameraPos -= cameraSpeed * ((glfwGetKey(window.window, GLFW_KEY_A) == GLFW_PRESS) - (glfwGetKey(window.window, GLFW_KEY_D) == GLFW_PRESS)) * glm::normalize(glm::cross(cameraFront, cameraUp));
            cameraPos -= cameraSpeed * ((glfwGetKey(window.window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) - (glfwGetKey(window.window, GLFW_KEY_SPACE) == GLFW_PRESS)) * cameraUp;
        }

        double lastX = 400, lastY = 300;
        double oldX = 0, oldY = 0;
        bool firstRun = true;
        float yaw = 0.0f;
        float pitch = 0.0f;

        //Rotates the Camera
        void RotateCamera(Window& window) {
            double xpos, ypos;
            glfwGetCursorPos(window.window, &xpos, &ypos);

            if (firstRun) {
                lastX = xpos;
                lastY = ypos;
                firstRun = false;
            }

            if (window.hasBeenPaused) {
                lastX = oldX;
                lastY = oldY;
                window.hasBeenPaused = false;
            }

            float xoffset = (xpos - lastX) * sensitivity;
            float yoffset = (lastY - ypos) * sensitivity;
            lastX = xpos;
            lastY = ypos;

            yaw += xoffset;
            pitch += yoffset;
            if (pitch > 89.0f) {
                pitch = 89.0f;
            }

            if (pitch < -89.0f) {
                pitch = -89.0f;
            }

            glm::vec3 direction;
            direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
            direction.y = sin(glm::radians(pitch));
            direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
            cameraFront = glm::normalize(direction);
        }

        //Returns projection * view matrix
        glm::mat4 cameraMatrix() {
            return glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f) * glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        }

};

#endif // CAMERA_H
