#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <Gui/Widgets/AbstractButton.h>

class Header : public QWidget
{
    public:
        Header();

    private:
        dvWidgets::AbstractButton* homeButton_;
        dvWidgets::AbstractButton* visButton_;
        dvWidgets::AbstractButton* dependenciesButton_;
        dvWidgets::AbstractButton* assetButton_;
        dvWidgets::AbstractButton* settingsButton_;


        QHBoxLayout* mainLayout_;
};
