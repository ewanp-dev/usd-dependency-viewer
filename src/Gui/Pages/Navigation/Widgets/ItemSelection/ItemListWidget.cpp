#include "ItemListWidget.h"

#include <QLayoutItem>

ItemListWidget::ItemListWidget(QWidget* parent)
{
    setWidgetResizable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setStyleSheet("background: transparent;");

    container_ = new QWidget(this);
    mainLayout_ = new QVBoxLayout(container_);
    mainLayout_->setContentsMargins(0, 0, 0, 0);
    mainLayout_->setSpacing(8);
    mainLayout_->addStretch();

    setWidget(container_);
}

void ItemListWidget::addItem(std::shared_ptr<DependencyNode> node)
{
    ItemWidget* item = new ItemWidget(node);
    items_.push_back(item);
    mainLayout_->insertWidget(mainLayout_->count() - 1, item);
}
void ItemListWidget::clearItems()
{
    for (ItemWidget* item : items_) {
        item->setParent(nullptr);
        item->deleteLater(); // safe, won't delete during event processing
    }
    items_.clear();

    QLayoutItem* child;
    while ((child = mainLayout_->takeAt(0))) {
        if (child->spacerItem())
        {
            mainLayout_->addItem(child->spacerItem());
            break;
        }
        delete child;  // just delete layout items, not widgets
    }
}

std::vector<ItemWidget*> ItemListWidget::getItems()
{
    return items_;
}
