#pragma once
#include <vector>
#include <glm/fwd.hpp>

enum ShaderType
{
    VERTEX,
    FRAGMENT
};

class Shader
{
public:
    Shader() = default;

    void Compile(std::vector<char>& source, ShaderType type);
    void Link();
    void Bind();
    void SetMatrixUniform(const char* name, glm::mat4 matrix);
private:
    unsigned int ShaderTypeToGLType(ShaderType type);
private:
    std::vector<unsigned int> m_shaders;
    unsigned int m_shaderProgram;
};
