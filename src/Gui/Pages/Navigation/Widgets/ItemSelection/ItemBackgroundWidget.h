#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Gui/Widgets/AbstractButton.h>
#include <Core/NodePath.h>

#include "ItemListWidget.h"

class ItemBackgroundWidget : public QWidget
{
    Q_OBJECT

    public:
        ItemBackgroundWidget(QWidget* parent = nullptr);

        ItemListWidget* getListWidget();
        void setActivePath(NodePath nodePath);

    private:
        void initHeader();
        void initBody();

        QHBoxLayout* headerLayout_;
        QVBoxLayout* mainLayout_;

        QLineEdit* searchBar_;
        dvWidgets::AbstractButton* filterButton_;

        ItemListWidget* itemArea_;

        NodePath nodePath_;
        std::shared_ptr<DependencyNode> activeNode_;
};
