#include "AbstractButton.h"

AbstractButton::AbstractButton(
    unsigned int width,
    unsigned int height,
    QWidget *parent
) 
{ 
    setFixedSize(width, height);
    setProperty("class", "AbstractButton");
}

void AbstractButton::setIconFromImage(const std::string& filePath, bool flipped, bool inverted) {
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

std::string AbstractButton::iconPath() {
    return filePath_;
}

QImage AbstractButton::invertImage_(QImage &image) {
    image.invertPixels(QImage::InvertMode::InvertRgb);
    return image;
}

QPixmap AbstractButton::flipPixmap_(QPixmap &pixmap) {
    QPixmap flipped = pixmap.transformed(QTransform().scale(-1, 1));
    return flipped;
}
