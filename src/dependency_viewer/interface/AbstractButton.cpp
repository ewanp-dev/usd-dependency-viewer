#include "AbstractButton.h"
#include <iostream>
#include <filesystem>
#include <QImage>
#include <QPixmap>

AbstractButton::AbstractButton(
    QWidget *parent,
    std::string iconName,
    std::string tooltip,
    unsigned int width,
    unsigned int height
) 
{
    
    setFixedSize(width, height);
    std::string currentDirectory = std::filesystem::current_path().string();
    if (!iconName.empty()) 
    { 
        iconPath = currentDirectory + "/src/dependency_viewer/interface/elements/"+ iconName;
        
        if (!std::filesystem::exists(iconPath))
        {
            std::cerr << "Warning: Icon file not found at " << iconPath << '\n';
        } else
        {
        std::cout << iconPath << '\n';
        QImage img = QImage(iconPath.c_str());
        QPixmap pixmap = QPixmap::fromImage(img);
        QIcon icon = QIcon(pixmap);

        this->setIcon(icon);
        setIconSize(QSize(width - 2, height - 2));
        }
    }

}
