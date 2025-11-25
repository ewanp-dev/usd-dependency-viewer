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
#include <Gui/Pages/Navigation/Widgets/FileProperties/FilePropertiesPage.h>
#include <Gui/Pages/Navigation/Widgets/UsdInspection/UsdInspectionPage.h>
#include <Gui/Pages/Navigation/Widgets/StackedWidgetHeader.h>

class NavigationStackedWidget : public QWidget
{
    public:
        NavigationStackedWidget(const std::vector<std::string>& dependencies, QWidget* parent = nullptr);
        
        Nodegraph* nodegraph();

    private:
        void initPages();

        QVBoxLayout*          mainLayout_;

        StackedWidgetHeader*  header_;
        QStackedWidget*       stackedPages_;
        Nodegraph*            nodegraph_;
        Viewport*             viewport_;
        FilePropertiesPage*   filePropertiesPage_;
        UsdInspectionPage*    usdInspectionPage_;

        const std::vector<std::string>& dependencies_;
};
