#pragma once

#include <qboxlayout.h>
#include <qtablewidget.h>
#include "Core/DependencyNode.h"
#include "Core/NodePath.h"
#include <QTextEdit>

class RecursiveTableWidget
: public QWidget
{
    public:
        RecursiveTableWidget();
        // void setActiveNode(std::shared_ptr<DependencyNode> node);
        void setActivePath(NodePath);
        const NodePath getActivePath() const;
    private:
        QTableWidget* table_;
        QVBoxLayout* mainLayout_;

        QWidget* header_;
        QLineEdit* headerPathWidget_;

        // NOTE: do not modify directly, use getters and setters
        NodePath nodePath_;

        std::shared_ptr<DependencyNode> activeNode_;

        void initHeader();
        void initTable();
        void initFooter();

        void onCellDoubleClicked(int row, int column);

    protected:
        virtual void resizeEvent(QResizeEvent *event);
};

