#include "FileReader.h"
#include <fstream>
#include <iostream>

std::vector<char> FileReader::ReadFile(std::string fileName)
{
    const std::string finalPath = SHADER_DIR + fileName + SHADER_FILE_EXTENSION;
    std::ifstream file = std::ifstream(finalPath, std::ios::ate | std::ios::binary);
    std::vector<char> buffer = std::vector<char>();

    if(!file.is_open())
    {
        std::cout << "Error, failed to open file at directory " << finalPath << "\n";
        return buffer;
    }

    const size_t fileSize = static_cast<size_t>(file.tellg());
    buffer.resize(fileSize);

    file.seekg(0);
    file.read(buffer.data(), static_cast<std::streamsize>(fileSize));
    file.close();

    buffer.push_back('\0');

    std::cout << "Successfully read shader file at " << finalPath << "\n";

    return buffer;
}
