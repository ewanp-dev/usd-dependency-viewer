#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QSplitter>
#include <string>
#include <vector>
#include <memory>

#include <Core/UsdDependencyGraph.h>
#include <Core/DependencyNode.h>
#include <Gui/Pages/Navigation/Widgets/RecursiveViewTable/RecursiveTableWidget.h>
#include <Gui/Pages/Navigation/Widgets/Nodegraph/Nodegraph.h>
#include <Gui/Pages/Navigation/Widgets/StackedWidget.h>
#include <Gui/Widgets/AbstractButton.h>

class NavigationPage : public QWidget
{
    Q_OBJECT

    public: 
        NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent = nullptr);
        void setActiveNode(std::shared_ptr<DependencyNode> node);

    private Q_SLOTS:
        void onTableCellDoubleClicked(std::shared_ptr<DependencyNode> node);
        void onTableNavUpButtonClicked(std::shared_ptr<DependencyNode> node);

    private:
        void initWidgets();

        const std::vector<std::string>& dependencies_;
        std::shared_ptr<UsdDependencyGraph> graph_;
        std::shared_ptr<DependencyNode> activeNode_;
        std::shared_ptr<DependencyNode> rootNode_;

        QWidget* pagesContainer_;
        QVBoxLayout* mainLayout_;
        QSplitter* mainSplitter_;

        RecursiveTableWidget* table_;
        NavigationStackedWidget* stackedWidget_;
        Nodegraph* nodegraph_;
};
