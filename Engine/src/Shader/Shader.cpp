#include "Shader.h"

#include <iostream>

#include "glad/glad.h"

void Shader::Compile(std::vector<char>& source, ShaderType type)
{
    std::string strSource = std::string(source.data());
    const char* sourceCString = strSource.c_str();
    
    unsigned int shader = glCreateShader(this->ShaderTypeToGLType(type));
    glShaderSource(shader, 1, &sourceCString, nullptr);
    glCompileShader(shader);

    int success;
    char info[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(shader, 512, nullptr, info);
        std::cout << "Error, shader compilation failed due to : " << info << "\n";
        return;
    }

    std::cout << "Successfully compiled shader \n";

    m_shaders.push_back(shader);
}

void Shader::Link()
{
    m_shaderProgram = glCreateProgram();
    for (unsigned int shader : m_shaders)
    {
        glAttachShader(m_shaderProgram, shader);
    }

    glLinkProgram(m_shaderProgram);

    int success;
    char info[512];
    glGetShaderiv(m_shaderProgram, GL_LINK_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(m_shaderProgram, 512, nullptr, info);
        std::cout << "Error, shader compilation failed due to : " << info << "\n";
        return;
    }

    for (unsigned int shader : m_shaders)
    {
        glDeleteShader(shader);
    }
    m_shaders.clear();

    std::cout << "Successfully linked shader(s) \n";
}

unsigned Shader::ShaderTypeToGLType(ShaderType type)
{
    switch (type)
    {
    case ShaderType::VERTEX:
        return GL_VERTEX_SHADER;
    case ShaderType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    }

    std::cout << "Error, could not recognize type of shader \n";
    return 0;
}

void Shader::Bind()
{
    glUseProgram(m_shaderProgram);
}


