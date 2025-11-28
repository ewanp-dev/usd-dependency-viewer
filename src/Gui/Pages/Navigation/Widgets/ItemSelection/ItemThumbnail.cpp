#include "ItemThumbnail.h"

#include <QSizePolicy>
#include <QPainter>
#include <QPainterPath>

ItemThumbnail::ItemThumbnail(QWidget* parent)
{
    setMinimumSize(150, 150);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

void ItemThumbnail::setThumbnail(const QPixmap& pixmap)
{
    thumbnail_ = pixmap;
}

void ItemThumbnail::clearThumbnail()
{
    setFallBackIcon();
    update();
}

void ItemThumbnail::paintEvent(QPaintEvent* event)
{
    QPainter painter = QPainter(this);
    
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    QPainterPath clipPath;
    clipPath.addRoundedRect(rect(), 8, 8);
    painter.setClipPath(clipPath);

    // NOTE:
    //
    // Hard-coding the color for now just to get a basic
    // widget out

    painter.fillRect(rect(), QColor("#716E6E"));

    QRect target = rect();
    target.setWidth(qMin(width(), height()));
    target.setHeight(qMin(width(), height()));
    target.moveCenter(rect().center());

    painter.drawPixmap(target, thumbnail_);
}

void ItemThumbnail::setFallBackIcon()
{
    setThumbnail(QPixmap(":/icons/DarkMode/camera.png")) ;
    update();
}
