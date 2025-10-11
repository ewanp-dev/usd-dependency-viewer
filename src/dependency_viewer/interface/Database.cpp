#include "Database.h"
#include "Globals.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QSizePolicy>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QHeaderView>
#include <vector>

DatabasePage::DatabasePage (const std::vector<std::string> &dependencies, QWidget* parent) {
    itemDependencies_ = dependencies;

    int paddingX = 5, paddingY = 5;
    QSize iconSize = QSize(18, 18);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* layoutHeader = new QHBoxLayout();

    layout->setContentsMargins(10, 10, 10, 10);
    layoutHeader->setContentsMargins(10, 5, 10, 5);

    resultsList_ = new AbstractButton();
    resultsList_->setFixedWidth(100);
    resultsList_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    resultsList_->setText(QString::number(static_cast<qulonglong>(dependencies.size())) + " Results");

    sort_ = new AbstractButton();
    sort_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    sort_->setIconFromImage(":icons/filter.png");

    properties_ = new AbstractButton();
    properties_->setSizePolicy(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Fixed);
    properties_->setIconFromImage(":icons/properties.png");

    resultsDropdown_ = new ResultsDropdownWidget();
    sortDropdown_ = new SortDropdownWidget();
    propertiesDropdown_ = new PropertiesDropdownWidget();

    connect(resultsList_, &AbstractButton::clicked, this, [this]() {
        showDropdown_(resultsList_, resultsDropdown_);
    });

    connect(sort_, &AbstractButton::clicked, this, [this]() {
        showDropdown_(sort_, sortDropdown_, 200);
    });

    connect(properties_, &AbstractButton::clicked, this, [this]() {
        showDropdown_(properties_, propertiesDropdown_, 100);
    });

    layoutHeader->addWidget(resultsList_);
    layoutHeader->addStretch(1);
    layoutHeader->addWidget(sort_);
    layoutHeader->addWidget(properties_);
    
    table_ = new QTableWidget(); 
    table_->resizeRowsToContents();
    table_->verticalHeader()->setVisible(false);
    table_->setRowCount(static_cast<int>(itemDependencies_.size()));
    table_->setColumnCount(5);
    table_->setColumnWidth(0, 400);
    table_->setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    table_->setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    table_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // NOTE: We might want to add some more columns later on down the line
    // might be worth converting this to its own QStringList as a variable
    table_->setHorizontalHeaderLabels({ "File Name", "File Path", "File Size", "Extension", "Date Modified" });
    table_->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeMode::Stretch);

    // TODO: Replace TableWidgetItems with correct options after USD Implementation
    // TODO: Look into making this more memory/speed efficient
    // TODO: Convert the font to a global font so we can use across the interface
    QFont itemFont = QFont("Sans Serif", 10);
    itemFont.setUnderline(true);
    for (size_t i = 0; i < itemDependencies_.size(); i++) {
        QTableWidgetItem *nameItem =  new QTableWidgetItem(itemDependencies_[i].c_str());
        QTableWidgetItem *pathItem = new QTableWidgetItem(itemDependencies_[i].c_str());
        QTableWidgetItem *fileSizeItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
        QTableWidgetItem *extensionItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));
        QTableWidgetItem *dateModifiedItem = new QTableWidgetItem(QString::number(static_cast<qulonglong>(i)));

        nameItem->setForeground(QBrush(QColor(210, 186, 146)));
        nameItem->setFont(itemFont);
        
        table_->setItem(i, 0, nameItem);
        table_->setItem(i, 1, pathItem);
        table_->setItem(i, 2, fileSizeItem);
        table_->setItem(i, 3, extensionItem);
        table_->setItem(i, 4, dateModifiedItem);
    }

    // -------
    // SET COLUMN PROPERTIES

    // table_->setColumnHidden(1, true);
    // table_->setColumnHidden(2, true);
    // table_->setColumnHidden(3, true);
    // table_->setColumnHidden(4, true);

    layout->addLayout(layoutHeader);
    layout->addWidget(table_);
}

void DatabasePage::showDropdown_(AbstractButton *button, QWidget *dropdown, int shift) {
    QPointF pos = button->mapToGlobal(button->rect().bottomLeft());
    if (shift > 0) {
        int posX = pos.x() - shift;
        pos.setX(posX);
    }

    dropdown->move(pos.x(), pos.y());
    dropdown->show();
}
