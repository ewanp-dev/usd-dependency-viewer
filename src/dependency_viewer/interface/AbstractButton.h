#pragma once
#include <QPushButton>

class AbstractButton : public QPushButton 
{
    public:
        AbstractButton(
        QWidget* parent, 
        std::string iconName,
        std::string tooltip,
        unsigned int width,
        unsigned int height
        );

    private:
        std::string iconPath;

};
