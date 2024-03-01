#pragma once
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class Window;

class Camera
{
public:
    Camera() = default;
    void Update(glm::mat4& viewMatrix, Window& window);
private:
    glm::vec3 m_forward = glm::vec3(0.0f, 0.0f, 1.0f);
    glm::vec3 m_right = glm::vec3(1.0f, 0.0f, 0.0f);
};
