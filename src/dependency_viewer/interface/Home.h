#pragma once

#include <QWidget>
#include <QLineEdit>
#include <QLabel>

class HomePage : public QWidget
{
    public:
        HomePage(QWidget *parent = nullptr);

    private:
        QLabel* homeLabel_;
        QLineEdit* search_;
};
