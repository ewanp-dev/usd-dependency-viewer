#include "Settings.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

SettingsWidget::SettingsWidget (QWidget *parent) {
    setWindowFlags(Qt::WindowFlags(Qt::FramelessWindowHint | Qt::Dialog));
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    setFixedSize(600, 600);

    exitButton_ = new AbstractButton();
    exitButton_->setText("Exit");
    exitButton_->setFixedWidth(100);

    QVBoxLayout *layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    topLayout->addWidget(exitButton_);
    layout->addLayout(topLayout);

    connect(exitButton_, &AbstractButton::clicked, this, &QWidget::close);

    setStyleSheet(R"(
        QWidget {
            background-color: rgb(12, 12, 12);
        }
    )");
}

void SettingsWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key::Key_Escape) {
        close();
    } else {
        QWidget::keyPressEvent(event);
    }
}
