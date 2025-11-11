#pragma once

#include <qboxlayout.h>
#include <qtablewidget.h>
#include <QStandardItemModel>
#include <QTextEdit>

#include <Gui/Widgets/AbstractTable.h>
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
        // void setActiveNode(std::shared_ptr<DependencyNode> node);
        void setActivePath(NodePath);
        const NodePath getActivePath() const;

    private:
        QStandardItemModel* model_;
        QVBoxLayout* mainLayout_;
        dvWidgets::AbstractTable* table_;

        QWidget* header_;
        QLineEdit* headerPathWidget_;

        // NOTE: do not modify directly, use getters and setters
        NodePath nodePath_;

        std::shared_ptr<DependencyNode> activeNode_;

        void initHeader();
        void initTable();
        void initFooter();

        void onCellDoubleClicked(const QModelIndex &);
        void onNavUpButtonClicked();
};

