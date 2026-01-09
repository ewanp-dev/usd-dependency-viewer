#pragma once

#include "ItemWidget.h"

#include <QScrollArea>
#include <QVBoxLayout>

#include <vector>

class ItemListWidget : public QScrollArea
{
    Q_OBJECT

    public:
        ItemListWidget(QWidget* parent = nullptr);

        void addItem(std::shared_ptr<DependencyNode> node);
        void clearItems();
        std::vector<ItemWidget*> getItems();

    private:
        QWidget* container_;
        QVBoxLayout* mainLayout_;

        std::vector<ItemWidget*> items_;
};
