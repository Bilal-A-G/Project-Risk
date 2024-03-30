#include "Mesh.h"
#include "glad/glad.h"
#include "../Shader/Shader.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "iostream"

const std::string TEXTURE_DIR = "../Client/textures/";
const std::string TEXTURE_FILE_EXTENSION = ".jpg";

void Mesh::Create(std::vector<float>& bufferData, std::vector<int>& indices, std::string texturePath)
{
    glGenVertexArrays(1, &m_VAO);
    glBindVertexArray(m_VAO);
    
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    this->SetTexture(texturePath);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * bufferData.size(), bufferData.data(), GL_STATIC_DRAW);  // NOLINT(bugprone-sizeof-container)

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * indices.size(), indices.data(), GL_STATIC_DRAW); // NOLINT(bugprone-sizeof-container)

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    m_numIndices = static_cast<int>(indices.size());
}

void Mesh::SetTexture(std::string texturePath)
{
    int width, height, nrChannels;
    unsigned char* data = stbi_load((TEXTURE_DIR + texturePath + TEXTURE_FILE_EXTENSION).c_str(), &width, &height, &nrChannels, 0);

    if (data != nullptr)
    {
        glGenTextures(1, &m_texture);
        glBindTexture(GL_TEXTURE_2D, m_texture);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        //std::cout << "Successfully loaded image at " << TEXTURE_DIR + texturePath + TEXTURE_FILE_EXTENSION << "\n";
    }
    else
    {
        //std::cout << "Failed to load image at " << TEXTURE_DIR + texturePath + TEXTURE_FILE_EXTENSION << "\n";
    }

    stbi_image_free(data);
}

void Mesh::Draw(Shader& shader)
{
    shader.Bind();
    shader.SetMatrixUniform("model", m_model);
    shader.SetMatrixUniform("view", m_view);
    shader.SetMatrixUniform("projection", m_projection);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_numIndices, GL_UNSIGNED_INT, nullptr);
    glBindVertexArray(0);
}

