#pragma once

#include "../../AbstractButton.h"
#include <QLineEdit>


class ResultsDropdownWidget : public QWidget
{
    public:
        ResultsDropdownWidget(QWidget *parent=nullptr);
    private:
        QLineEdit *limit_;
        AbstractButton *reset_;
        AbstractButton *copy_;
};
