#pragma once 

#include "../AbstractButton.h"
#include <QWidget>
#include <QKeyEvent>

class SettingsWidget : public QWidget 
{
    public:
        SettingsWidget(QWidget *parent=nullptr);
    private:
        void keyPressEvent(QKeyEvent *event) override;
        AbstractButton *exitButton_;
};
