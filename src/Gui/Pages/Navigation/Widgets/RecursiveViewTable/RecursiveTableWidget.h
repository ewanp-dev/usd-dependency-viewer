#pragma once

#include <QHBoxLayout>
#include <QTableWidget>
#include <QStandardItemModel>
#include <QTextEdit>

#include <Gui/Pages/Navigation/Widgets/RecursiveViewTable/TableHeader.h>
#include <Gui/Widgets/AbstractTable/AbstractTable.h>
#include <Core/NodePath.h>
#include <Core/DependencyNode.h>

class RecursiveTableWidget
: public QWidget
{
    Q_OBJECT

    Q_SIGNALS:
        void cellDoubleClicked(std::shared_ptr<DependencyNode> node);
        void navUpButtonClicked(std::shared_ptr<DependencyNode> node);

    public:
        RecursiveTableWidget();
        void setActivePath(NodePath);
        const NodePath getActivePath() const;

    private:
        QVBoxLayout* mainLayout_;

        QStandardItemModel* model_;
        TableHeader* tableHeader_;
        AbstractTable* table_;
        QStringList columns_;

        // NOTE: do not modify directly, use getters and setters
        NodePath nodePath_;

        std::shared_ptr<DependencyNode> activeNode_;

        void initTable();

        void onCellDoubleClicked(const QModelIndex &);
        void onNavUpButtonClicked();
};

