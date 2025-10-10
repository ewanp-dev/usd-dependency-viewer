#include "AbstractButton.h"
#include <iostream>
#include <filesystem>

AbstractButton::AbstractButton(
    unsigned int width,
    unsigned int height,
    QWidget *parent
) 
{ 
    setFixedSize(width, height);
    setStyleSheet(R"(
        QPushButton {
            border: none;
            color: rgb(210, 210, 210);
            background: transparent;
            padding: 4px 4px;
        }
        QPushButton:hover {
            background-color: rgb(60, 60, 60);
        }
    )");
}

void AbstractButton::setIconFromImage(const std::string& filePath, bool flipped, bool inverted) {
    this->filePath_ = filePath;
    if (!std::filesystem::exists(filePath)) {
        std::cerr << "Warning: Icon file not found at " << filePath << '\n';
    } else {
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
}

void AbstractButton::setPadding(int x, int y) {
    QString style = QString("padding: %1px %2px;").arg(x).arg(y);
    setStyleSheet(style);
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
