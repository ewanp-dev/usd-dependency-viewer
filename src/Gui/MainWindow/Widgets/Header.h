#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <Gui/Widgets/AbstractButton.h>

class Header : public QWidget
{
    public:
        Header();

    private:
        AbstractButton* homeButton_;
        AbstractButton* visButton_;
        AbstractButton* listButton_;
        AbstractButton* assetButton_;
        AbstractButton* settingsButton_;

        QHBoxLayout* mainLayout_;
};
