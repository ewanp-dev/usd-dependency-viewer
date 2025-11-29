#pragma once

#include <QWidget>
#include <QPixmap>
#include <QPaintEvent>

class ItemThumbnail : public QWidget
{
    Q_OBJECT

    public:
        ItemThumbnail(QWidget* parent = nullptr);

        void setThumbnail(const QPixmap& pixmap);
        void clearThumbnail();

    protected:
        void paintEvent(QPaintEvent* event) override;

    private:
        void setFallBackIcon();

        QPixmap thumbnail_;
};
