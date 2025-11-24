#pragma once

#include <QHBoxLayout>
#include <QTextEdit>

#include <Core/NodePath.h>
#include <Core/DependencyNode.h>
#include <Gui/Widgets/AbstractTable/AbstractTable.h>
#include <Gui/Pages/Navigation/Widgets/RecursiveViewTable/TableHeader.h>

// NOTE:
// Attempting a simplified version of the 
// RecursiveTableWidget to make the AbstractTable
// more modular
// 
// Add in the signals and slots from other class

class RecursiveTableWidget : public QWidget
{
    Q_OBJECT

    public:
        RecursiveTableWidget(QWidget* parent = nullptr);

        void setActivePath(NodePath);
        const NodePath getActivePath() const;

    private:
        void initTable();
        void initWidget();

        QVBoxLayout*    mainLayout_;
        AbstractTable*  table_;
        NodePath        nodePath_;
        std::shared_ptr<DependencyNode> activeNode_;
};
