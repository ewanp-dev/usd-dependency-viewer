#pragma once

#include <QWidget>
#include <QPushButton>
#include <QTimer>
#include <QElapsedTimer>

class HomePage : public QWidget
{
    public:
        HomePage();
        void mouseMoveEvent(QMouseEvent *event) override;
        // void paintEvent(QPaintEvent *event) override;
        QPushButton *searchButton;

    private:
        void updateAnimation();
        int offset_;
        QPointF mousePos_;
        QTimer *timer_;
        
};
