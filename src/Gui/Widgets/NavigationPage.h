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
#include <Gui/Widgets/Nodegraph/Nodegraph.h>
#include <Gui/Widgets/ItemSelection/ItemBackgroundWidget.h>
#include <Gui/Widgets/RecursiveViewTable/TableHeader.h>
#include <Gui/Widgets/AbstractWidgets/AbstractButton.h>
#include <Gui/Widgets/Properties/PropertiesWidget.h>

class NavigationPage : public QWidget
{
    Q_OBJECT

    private Q_SLOTS:
        void onItemWidgetDoubleClicked(const std::string& filePath);
        void onItemWidgetActivated(const std::string& filePath);
        void onNodeDoubleClicked(const std::string& filePath);

    public: 
        NavigationPage(const std::vector<std::string>& dependencies, std::shared_ptr<UsdDependencyGraph> graph, QWidget* parent = nullptr);
        void setActiveNode(NodePath nodePath);
        const NodePath getActivePath() const;

    private:
        void initWidgets();
        void onNavUpButtonClicked(std::shared_ptr<DependencyNode> node);

        const std::vector<std::string>& dependencies_;
        std::shared_ptr<UsdDependencyGraph> graph_;
        std::shared_ptr<DependencyNode> activeNode_;
        std::shared_ptr<DependencyNode> rootNode_;
        NodePath nodePath_;

        QWidget* pagesContainer_;
        QVBoxLayout* mainLayout_;
        QSplitter* mainSplitter_;

        TableHeader* header_;
        ItemBackgroundWidget* itemBackgroundWidget_;
        ItemListWidget* itemArea_;
        Nodegraph* nodegraph_;
        PropertiesWidget* properties_;
};
