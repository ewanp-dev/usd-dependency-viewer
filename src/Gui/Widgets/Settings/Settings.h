#pragma once 

#include <QWidget>
#include <QKeyEvent>

#include <Gui/Widgets/AbstractWidgets/AbstractButton.h>

class SettingsWidget : public QWidget 
{
    public:
        SettingsWidget(QWidget *parent=nullptr);
    private:
        void keyPressEvent(QKeyEvent *event) override;
        dvWidgets::AbstractButton *exitButton_;
};
