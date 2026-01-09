#pragma once

#include <QPushButton>
#include <QImage>
#include <QPixmap>

#include <Gui/Globals.h>

namespace dvWidgets
{
class AbstractButton : public QPushButton 
{
    Q_OBJECT

    public:
        AbstractButton(
            unsigned int width = DV_BUTTON_WIDTH,
            unsigned int height = DV_BUTTON_HEIGHT, 
            QWidget* parent = nullptr 
        );

        void enableHoverEvent(bool condition = true);
        void setIconFromImage(const std::string& filePath, bool flipped = false, bool inverted = DV_ICONS_INVERTED);
        std::string iconPath();

    protected:
        void enterEvent(QEnterEvent* event) override;
        void leaveEvent(QEvent* event)      override;

    private:
        QImage invertImage_(QImage &img);
        QPixmap flipPixmap_(QPixmap &pixmap);
        
        std::string filePath_;
        bool        hoverEvents_;
        QColor      startColor_;
        QColor      endColor_;

};
}
