#pragma once
#include <vector>

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
private:
    unsigned int ShaderTypeToGLType(ShaderType type);
private:
    std::vector<unsigned int> m_shaders;
    unsigned int m_shaderProgram;
};
