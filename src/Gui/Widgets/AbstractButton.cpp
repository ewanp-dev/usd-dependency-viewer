#include "AbstractButton.h"
#include "AbstractWidgetUtils.h"

#include <iostream>

dvWidgets::AbstractButton::AbstractButton(
    unsigned int width,
    unsigned int height,
    QWidget *parent
) 
    : startColor_(QColor("#262626")), endColor_(QColor("#799E94"))
{ 
    // setFixedSize(width, height);
    setProperty("class", "AbstractButton");
    setAttribute(Qt::WA_Hover);
    setMouseTracking(true);

    hoverEvents_ = true;
}

void dvWidgets::AbstractButton::enableHoverEvent(bool condition)
{
    hoverEvents_ = condition;
}

void dvWidgets::AbstractButton::setIconFromImage(const std::string& filePath, bool flipped, bool inverted) {
    this->filePath_ = filePath;
    QImage img = QImage(filePath.c_str());
    if (inverted) {
        invertImage_(img);
    }
    QPixmap pixmap = QPixmap::fromImage(img);
    if (flipped) {
        pixmap = flipPixmap_(pixmap);
    }
    QIcon icon = QIcon(pixmap);
    setIcon(icon);
    setIconSize(QSize(width() - 2, height() - 2));
}

std::string dvWidgets::AbstractButton::iconPath() {
    return filePath_;
}

QImage dvWidgets::AbstractButton::invertImage_(QImage &image) {
    image.invertPixels(QImage::InvertMode::InvertRgb);
    return image;
}

QPixmap dvWidgets::AbstractButton::flipPixmap_(QPixmap &pixmap) {
    QPixmap flipped = pixmap.transformed(QTransform().scale(-1, 1));
    return flipped;
}

void dvWidgets::AbstractButton::enterEvent(QEnterEvent* event)
{
    if (hoverEvents_)
        dvWidgets::AbstractWidgetUtils::animateColor(this, startColor_, endColor_);
}

void dvWidgets::AbstractButton::leaveEvent(QEvent* event)
{
    if (hoverEvents_)
        dvWidgets::AbstractWidgetUtils::animateColor(this, endColor_, startColor_);
}
