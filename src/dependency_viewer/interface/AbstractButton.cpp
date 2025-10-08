#include "AbstractButton.h"
#include <iostream>
#include <filesystem>

AbstractButton::AbstractButton(
    QWidget *parent,
    std::string iconName,
    std::string tooltip,
    unsigned int width,
    unsigned int height
) 
{
    std::string currentDirectory = std::filesystem::current_path().string();
    if (!iconName.empty()) iconPath = currentDirectory + "/interface/elements/"+ iconName;
    std::cout << iconName << '\n';
    std::cout << currentDirectory << '\n';
    std::cout << iconPath << '\n';
}
