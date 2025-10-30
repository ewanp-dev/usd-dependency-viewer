#pragma once 

#include <QWidget>
#include <QKeyEvent>
#include <Gui/Widgets/AbstractButton.h>

class SettingsWidget : public QWidget 
{
    public:
        SettingsWidget(QWidget *parent=nullptr);
    private:
        void keyPressEvent(QKeyEvent *event) override;
        AbstractButton *exitButton_;
};
