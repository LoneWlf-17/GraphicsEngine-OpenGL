#include "GE/HelperClasses/Input.h"

void GE::Input::processInput(GLFWwindow* window, glm::vec3* cameraPos, glm::vec3* cameraFront, glm::vec3* cameraUp, float cameraSpeed)
{
    currentTime = (float)glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, 1);
    }
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        *cameraPos += *cameraFront * deltaTime * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        *cameraPos -= *cameraFront * deltaTime * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        *cameraPos -= glm::normalize(glm::cross(*cameraFront, *cameraUp)) * deltaTime * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        *cameraPos += glm::normalize(glm::cross(*cameraFront, *cameraUp)) * deltaTime * cameraSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        *cameraPos += *cameraUp * cameraSpeed * deltaTime;
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
    {
        *cameraPos -= *cameraUp * cameraSpeed * deltaTime;
    }
}
