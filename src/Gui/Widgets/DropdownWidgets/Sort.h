#pragma once

#include <QWidget>
#include <QComboBox>
#include <QStringList>
#include <Gui/Widgets/AbstractButton.h>

class SortDropdownWidget : public QWidget 
{
    public:
        SortDropdownWidget(QWidget *parent=nullptr);
    private:
        QComboBox *sortType_;
        QComboBox *sortRule_;
        dvWidgets::AbstractButton *clearSort_;
        QStringList typesList_;
};
