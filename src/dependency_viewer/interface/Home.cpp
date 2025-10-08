#include "Home.h"
#include <QMouseEvent>

HomePage::HomePage() {
    offset_ = 0;
    
    timer_ = new QTimer(this);
    timer_->setTimerType(Qt::TimerType::PreciseTimer);
    connect(timer_, &QTimer::timeout, this, &HomePage::updateAnimation);

    const int fps = 60;
    constexpr int interval = static_cast<float>(1000) / fps;

    timer_->start(interval);

    setMouseTracking(true);
    mousePos_ = QPointF(static_cast<float>(width()) / 2, static_cast<float>(height()) / 2);

    searchButton = new QPushButton("Search", this);

    searchButton->move(
        static_cast<int>(
            (static_cast<float>(width()) / 2)
            + static_cast<float>(width()) / 2
            - ((mousePos_.x() - static_cast<float>(width()) / 2) * 0.05)
        ),
        static_cast<int>(
            (static_cast<float>(height()) / 2)
            + 10
            - ((mousePos_.y() - static_cast<float>(height()) / 2) * 0.05)
        )
    );
}

void HomePage::updateAnimation() {
    offset_ += 0.05;
    update();
}

void HomePage::mouseMoveEvent(QMouseEvent *event) {
    mousePos_ = event->position();
} 
