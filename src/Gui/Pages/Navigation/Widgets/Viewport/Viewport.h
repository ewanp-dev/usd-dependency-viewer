#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Viewport : public QWidget
{
    public:
        Viewport(QWidget* parent = nullptr);

    private:
        QVBoxLayout* mainLayout_;

        QLabel* label_;
};
