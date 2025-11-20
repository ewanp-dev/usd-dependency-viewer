#pragma once

#include <QPushButton>
#include <QImage>
#include <QPixmap>

#include <Gui/MainWindow/Globals.h>

namespace dvWidgets
{
class AbstractButton : public QPushButton 
{
    public:
        AbstractButton(
            unsigned int width = DV_BUTTON_WIDTH,
            unsigned int height = DV_BUTTON_HEIGHT, 
            QWidget* parent = nullptr 
        );
        void setIconFromImage(const std::string& filePath, bool flipped = false, bool inverted = DV_ICONS_INVERTED);
        std::string iconPath();

    private:
        QImage invertImage_(QImage &img);
        QPixmap flipPixmap_(QPixmap &pixmap);
        std::string filePath_;
};
}
