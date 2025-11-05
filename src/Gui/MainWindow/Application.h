#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <Gui/Pages/Home/Home.h>
#include <Core/UsdDependencyGraph.h>
#include <Gui/MainWindow/Widgets/Search.h>
#include <Gui/MainWindow/Widgets/Header.h>
#include <Gui/MainWindow/Widgets/Sidebar.h>
#include <Gui/MainWindow/Widgets/Tree.h>
#include <Gui/Pages/Navigation/NavigationPage.h>
#include <Gui/Pages/Settings/Settings.h>
#include <Gui/Pages/Home/Home.h>

class DependencyViewer : public QMainWindow 
{
    public:
        DependencyViewer(std::string startFile = "", QWidget *parent = nullptr);
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
        NavigationPage* navPage_;
        HomePage *homePage_;
        std::shared_ptr<UsdDependencyGraph> dependencyGraph_;
};
