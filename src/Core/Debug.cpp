#include "Debug.h"

#include <algorithm>
#include <filesystem>

std::string dvCore::UsdDebug::getFileExtension(const std::string& filePath)
{
    std::filesystem::path path(filePath);
    std::string extension = path.extension().string();

    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    return extension;
}
