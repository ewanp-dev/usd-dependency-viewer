#pragma once

#include <QLineEdit>

#include <Gui/Widgets/AbstractWidgets/AbstractButton.h>

class ResultsDropdownWidget : public QWidget
{
    public:
        ResultsDropdownWidget(QWidget *parent=nullptr);
    private:
        QLineEdit *limit_;
        dvWidgets::AbstractButton *reset_;
        dvWidgets::AbstractButton *copy_;
};
