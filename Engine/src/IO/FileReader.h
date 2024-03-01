#pragma once
#include <vector>
#include <string>

const std::string SHADER_DIR = "../Client/shaders/";
const std::string SHADER_FILE_EXTENSION = ".glsl";

class FileReader
{
public:
    FileReader() = delete;
    ~FileReader() = delete;

    static std::vector<char> ReadFile(std::string fileName);
};
