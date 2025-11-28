#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QSplitter>
#include <Core/UsdDependencyGraph.h>
#include <Gui/Pages/Home/Home.h>
#include <Gui/MainWindow/Widgets/Search.h>
#include <Gui/MainWindow/Widgets/Header.h>
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
        void initStyleSheet();
        void initFonts();
        void initPages(std::vector<std::string> dependencies);
        void initWidgets(std::vector<std::string> dependencies);
        void showFloatingWidget(QWidget* widget);

        int savedWidth_ = 200;
        const std::string&                  startFile_;
        std::vector<std::string>            itemDependencies_;
        std::vector<std::string>            flattenedDependencies_;
        std::shared_ptr<UsdDependencyGraph> dependencyGraph_;
        int numDependencies_;

        QWidget*        centralWidget_;
        QVBoxLayout*    mainLayout_;
        QStackedWidget* mainPages_;

        Header*   header_;
        HomePage* homePage_;
        Footer*   footer_;

        SearchWidget*   searchWidget_;
        SettingsWidget* settingsWidget_;

        NavigationPage*       navigationPage_;
        AssetViewPage*        assetViewPage_;
        DependenciesListPage* dependenciesListPage_;
};
