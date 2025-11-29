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
        dvWidgets::AbstractButton* getFiltersButton();
        dvWidgets::AbstractButton* getHomeButton();
        dvWidgets::AbstractButton* getNavigationButton();

    private:
        void initHeader();
        void initBody();
        dvWidgets::AbstractButton* initButton(const std::string& iconPath);

        QHBoxLayout* headerLayout_;
        QVBoxLayout* mainLayout_;

        QLineEdit* searchBar_;
        dvWidgets::AbstractButton* filterButton_;
        dvWidgets::AbstractButton* homeButton_;
        dvWidgets::AbstractButton* upButton_;

        const int FIXED_BUTTON_SIZE_ = 20;
        const QSize FIXED_ICON_SIZE_ = QSize(18, 18);

        ItemListWidget* itemArea_;

        NodePath nodePath_;
        std::shared_ptr<DependencyNode> activeNode_;
};
