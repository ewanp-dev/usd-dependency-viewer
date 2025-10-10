#pragma once

#include "../../AbstractButton.h"
#include <QWidget>
#include <QComboBox>
#include <QStringList>

class SortDropdownWidget : public QWidget 
{
    public:
        SortDropdownWidget(QWidget *parent=nullptr);
    private:
        QComboBox *sortType_;
        QComboBox *sortRule_;
        AbstractButton *clearSort_;
        QStringList typesList_;
};
