#pragma once

#include <QWidget>
#include <QScrollArea>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <Gui/Widgets/AbstractButton.h>

class ItemBackgroundWidget : public QWidget
{
    Q_OBJECT

    public:
        ItemBackgroundWidget(QWidget* parent = nullptr);

    private:
        void initHeader();
        void initBody();

        QHBoxLayout* headerLayout_;
        QVBoxLayout* mainLayout_;

        QLineEdit* searchBar_;
        dvWidgets::AbstractButton* filterButton_;

        QScrollArea* itemArea_;
};
