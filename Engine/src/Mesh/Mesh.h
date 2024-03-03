#pragma once
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include "vector"

class Shader;

class Mesh
{
public:
    Mesh() = default;
    void Create(std::vector<glm::vec3>& vertices, std::vector<int>& indices);
    void Draw(Shader& shader);
    
    void SetView(glm::mat4 view){m_view = view;}
    void SetProjection(glm::mat4 projection){m_projection = projection;}
    void SetModel(glm::mat4 model){m_model = model;}
private:
    unsigned int m_VAO;
    unsigned int m_VBO;
    unsigned int m_EBO;
    int m_numIndices;
    
    glm::mat4 m_model = glm::mat4(1);
    glm::mat4 m_view = glm::mat4(1);
    glm::mat4 m_projection = glm::mat4(1);
};
