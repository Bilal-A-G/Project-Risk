#pragma once
#include <glm/vec3.hpp>
#include "vector"

class Shader;

class Mesh
{
public:
    Mesh() = default;
    void Create(std::vector<glm::vec3>& vertices, std::vector<int>& indices);
    void Draw(Shader& shader);
private:
    unsigned int m_VAO;
    int m_numIndices;
};
