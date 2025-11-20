#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <string>
#include <vector>

#include <Gui/Widgets/AbstractButton.h>
#include <Gui/Pages/Navigation/Widgets/Nodegraph/Nodegraph.h>
#include <Gui/Pages/Navigation/Widgets/Viewport/Viewport.h>

class NavigationStackedWidget : public QWidget
{
    public:
        NavigationStackedWidget(const std::vector<std::string>& dependencies, QWidget* parent = nullptr);
        
        Nodegraph* nodegraph();

    private:
        void initPages();
        void onButtonClicked(dvWidgets::AbstractButton* button, int index);
        dvWidgets::AbstractButton* initButton(const std::string& text, int index);

        QVBoxLayout* mainLayout_;
        QHBoxLayout* buttonsLayout_;
        QStackedWidget* stackedPages_;

        Nodegraph* nodegraph_;
        Viewport* viewport_;

        dvWidgets::AbstractButton* nodegraphButton_;
        dvWidgets::AbstractButton* viewportButton_;
        dvWidgets::AbstractButton* filePropertiesButton_;
        dvWidgets::AbstractButton* usdInspectionButton_;

        const std::vector<std::string>& dependencies_;
        std::vector<dvWidgets::AbstractButton*> buttons_;
};
