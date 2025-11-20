#pragma once

#include <Gui/Widgets/AbstractButton.h>
#include <QLineEdit>

class ResultsDropdownWidget : public QWidget
{
    public:
        ResultsDropdownWidget(QWidget *parent=nullptr);
    private:
        QLineEdit *limit_;
        dvWidgets::AbstractButton *reset_;
        dvWidgets::AbstractButton *copy_;
};
