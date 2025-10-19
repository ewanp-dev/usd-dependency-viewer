#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include "Home.h"
#include "Gui/pages/RecursiveViewPage/RecursiveViewPage.h"
#include "Nodegraph.h"
#include "widgets/Tree.h"
#include "widgets/Sidebar.h"
#include "widgets/Settings.h"
#include "widgets/Header.h"
#include "widgets/Search.h"
#include "Core/UsdDependencyGraph.h"

class DependencyViewer : public QMainWindow 
{
    public:
        DependencyViewer(QWidget *parent = nullptr);
    private:
        void showFloatingWidget_(QWidget* widget);
        void expandDropdown_(bool checked);
        void initStyleSheet();
        void initFonts();
        std::vector<std::string> itemDependencies_;
        int savedWidth_;
        SearchWidget* searchWidget_;
        SettingsWidget* settingsWidget_;
        DependenciesTreeWidget* treeWidget_;
        Sidebar *sidebar_;
        Header *header_;
        RecursiveViewPage *databasePage_;
        NodegraphPage *nodegraphPage_;
        HomePage *homePage_;
        UsdDependencyGraph* dependencyGraph_;
};
