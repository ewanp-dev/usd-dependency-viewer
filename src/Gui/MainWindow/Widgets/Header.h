#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <vector>
#include <Gui/Widgets/AbstractButton.h>

class Header : public QWidget
{
    public:
        Header(QWidget* parent = nullptr);

        dvWidgets::AbstractButton* homeButton();
        dvWidgets::AbstractButton* visualizationButton();
        dvWidgets::AbstractButton* dependenciesButton();
        dvWidgets::AbstractButton* assetButton();
        dvWidgets::AbstractButton* settingsButton();

    private:
        dvWidgets::AbstractButton* initButton(
            const std::string& text, 
            const std::string& iconPath, 
            bool enableSignals = true 
        );

        QHBoxLayout*               mainLayout_;

        dvWidgets::AbstractButton* homeButton_;
        dvWidgets::AbstractButton* visButton_;
        dvWidgets::AbstractButton* dependenciesButton_;
        dvWidgets::AbstractButton* assetButton_;
        dvWidgets::AbstractButton* settingsButton_;

        std::vector<dvWidgets::AbstractButton*> headerButtons_;

        const int   FIXED_HEADER_HEIGHT_ = 40;
        const int   FIXED_BUTTON_HEIGHT_ = 30;
        const int   FIXED_FONT_SIZE_     = 10;
        const QSize FIXED_ICON_SIZE_     = QSize(FIXED_FONT_SIZE_ + 4, FIXED_FONT_SIZE_ + 4);
};
