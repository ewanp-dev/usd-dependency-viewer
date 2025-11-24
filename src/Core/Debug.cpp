#include "Debug.h"

#include <algorithm>
#include <filesystem>
#include <fstream>

void dvCore::UsdDebug::writeVectorToFile(const std::string& fileName, const std::vector<std::string>& inputVector)
{

    std::ofstream out(fileName, std::ios::out | std::ios::trunc);
    if (!out) return; // handle error as needed

    for (const std::string& s : inputVector)
        out << s << '\n';
}

std::string dvCore::UsdDebug::getFileExtension(const std::string& filePath)
{
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    return extension;
}
