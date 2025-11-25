#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <vector>
#include <Gui/Widgets/AbstractButton.h>

class StackedWidgetHeader : public QWidget
{
    public:
        StackedWidgetHeader(QWidget* parent = nullptr);

        dvWidgets::AbstractButton* nodegraphPageButton();
        dvWidgets::AbstractButton* viewportPageButton();
        dvWidgets::AbstractButton* filePropertiesPageButton();
        dvWidgets::AbstractButton* usdInspectionPageButton();

    private:
        dvWidgets::AbstractButton* initButton(const std::string& text);

        QWidget*                   headerWrapper_;
        QHBoxLayout*               mainLayout_;

        dvWidgets::AbstractButton* nodegraphButton_;
        dvWidgets::AbstractButton* viewportButton_;
        dvWidgets::AbstractButton* filePropertiesButton_;
        dvWidgets::AbstractButton* usdInspectionButton_;

        std::vector<dvWidgets::AbstractButton*> headerButtons_;
};
