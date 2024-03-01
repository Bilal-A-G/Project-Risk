#include "Mesh.h"
#include "glad/glad.h"
#include "../Shader/Shader.h"

void Mesh::Create(std::vector<glm::vec3>& vertices, std::vector<int>& indices)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    unsigned int VBO;
    unsigned int EBO;
    
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices.data(), GL_STATIC_DRAW);  // NOLINT(bugprone-sizeof-container)

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices.data(), GL_STATIC_DRAW); // NOLINT(bugprone-sizeof-container)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    m_numIndices = static_cast<int>(indices.size());
}

void Mesh::Draw(Shader& shader)
{
    shader.Bind();
    shader.SetMatrixUniform("model", m_model);
    shader.SetMatrixUniform("view", m_view);
    shader.SetMatrixUniform("projection", m_projection);
    
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
}

