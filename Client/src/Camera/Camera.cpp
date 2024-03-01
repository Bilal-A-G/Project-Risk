#include "Camera.h"

#include <iostream>
#include <glm/ext/matrix_transform.hpp>

#include "GLFW/glfw3.h"
#include "Window/Window.h"

constexpr float cameraSpeed = 0.01f;
constexpr float mouseSensitivity = 0.05f;
bool mouseDown;

double cursorX;
double cursorY;

double cursorXLastFrame;
double cursorYLastFrame;

void Camera::Update(glm::mat4& viewMatrix, Window& window)
{
    if(window.GetKeyDown(GLFW_KEY_W))
    {
        viewMatrix = glm::translate(viewMatrix, m_forward * cameraSpeed);
    }
    if(window.GetKeyDown(GLFW_KEY_S))
    {
        viewMatrix = glm::translate(viewMatrix, -m_forward * cameraSpeed);
    }
    if(window.GetKeyDown(GLFW_KEY_A))
    {
        viewMatrix = glm::translate(viewMatrix, m_right * cameraSpeed);
    }
    if(window.GetKeyDown(GLFW_KEY_D))
    {
        viewMatrix = glm::translate(viewMatrix, -m_right * cameraSpeed);
    }

    mouseDown = window.GetMouseButtonDown(GLFW_MOUSE_BUTTON_RIGHT);
    window.GetCursorPosition(cursorX, cursorY);
    double mouseDeltaX = cursorX - cursorXLastFrame;
    double mouseDeltaY = cursorY - cursorYLastFrame;
    
    if(mouseDown)
    {
        window.SetCursorInputMode(GLFW_CURSOR_DISABLED);
        viewMatrix = glm::rotate(viewMatrix,  static_cast<float>(mouseDeltaX * mouseSensitivity),  glm::vec3(0.0f, 1.0f, 0.0f));
        viewMatrix = glm::rotate(viewMatrix,  static_cast<float>(mouseDeltaY * mouseSensitivity), m_right);
    }
    else
    {
        window.SetCursorInputMode(GLFW_CURSOR_NORMAL);
    }

    cursorXLastFrame = cursorX;
    cursorYLastFrame = cursorY;
}
