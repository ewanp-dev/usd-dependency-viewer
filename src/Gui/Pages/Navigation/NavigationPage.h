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

class NavigationPage : public QWidget
{
    public: 
        NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent = nullptr);
        void setActiveNode(std::shared_ptr<DependencyNode> node);

    private:
        QVBoxLayout* mainLayout_;
        QSplitter* mainSplitter_;
        QStackedWidget* stackedWidget_;

        std::shared_ptr<DependencyNode> activeNode_;

};
