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

        const int FIXED_HEADER_HEIGHT_ = 40;
        const int FIXED_BUTTON_HEIGHT_ = 26;
        const int FIXED_FONT_SIZE_ = 10;
        const QSize FIXED_ICON_SIZE_ = QSize(FIXED_FONT_SIZE_ + 4, FIXED_FONT_SIZE_ + 4);

        dvWidgets::AbstractButton* initButton(const std::string& text, const std::string& iconPath);

        QHBoxLayout* mainLayout_;
};
