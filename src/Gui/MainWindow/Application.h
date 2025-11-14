#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <Gui/Pages/Home/Home.h>
#include <Core/UsdDependencyGraph.h>
#include <Gui/MainWindow/Widgets/Search.h>
#include <Gui/MainWindow/Widgets/Header.h>
#include <Gui/MainWindow/Widgets/Tree.h>
#include <Gui/MainWindow/Widgets/Footer.h>
#include <Gui/Pages/AssetView/AssetView.h>
#include <Gui/Pages/DependenciesList/DependenciesList.h>
#include <Gui/Pages/Navigation/NavigationPage.h>
#include <Gui/Pages/Settings/Settings.h>
#include <Gui/Pages/Home/Home.h>

class DependencyViewer : public QMainWindow 
{
    public:
        DependencyViewer(const std::string& startFile = "", QWidget* parent = nullptr);

    private:
        void showFloatingWidget(QWidget* widget);
        void expandDropdown_(bool checked);
        void initPages();
        void initWidgets();
        void initStyleSheet();
        void initFonts();

        int savedWidth_;
        std::vector<std::string> itemDependencies_;
        std::shared_ptr<UsdDependencyGraph> dependencyGraph_;

        QWidget* centralWidget_;
        QVBoxLayout* mainLayout_;

        SearchWidget* searchWidget_;
        SettingsWidget* settingsWidget_;
        DependenciesTreeWidget* treeWidget_;
        Header *header_;
        HomePage *homePage_;
        Footer* footer_;

        NavigationPage* navigationPage_;
        AssetViewPage* assetViewPage_;
        DependenciesListPage* dependenciesListPage_;

};
