#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QStackedWidget>
#include <QSplitter>
#include <string>
#include <vector>
#include <memory>

#include <Gui/Pages/Navigation/Widgets/RecursiveView/RecursiveTableWidget.h>
#include <Gui/Pages/Navigation/Widgets/Nodegraph/Nodegraph.h>
#include <Gui/Pages/Navigation/Widgets/Header/Header.h>
#include <Core/UsdDependencyGraph.h>
#include <Core/DependencyNode.h>

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
        QVBoxLayout* mainLayout_;
        QSplitter* mainSplitter_;
        QStackedWidget* stackedWidget_;
        RecursiveTableWidget* table_;
        Nodegraph* nodegraph_;
        NavigationHeader* header_;

        std::shared_ptr<DependencyNode> activeNode_;
        std::shared_ptr<DependencyNode> rootNode_;

};
