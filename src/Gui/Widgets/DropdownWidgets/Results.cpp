#include "Results.h"

#include <QVBoxLayout>

ResultsDropdownWidget::ResultsDropdownWidget(QWidget *parent) {
    setWindowFlags(Qt::WindowFlags(windowFlags() | Qt::WindowType::Popup));

    QVBoxLayout *layout = new QVBoxLayout(this);
    limit_ = new QLineEdit();

    reset_ = new dvWidgets::AbstractButton();
    reset_->setIconFromImage("sorting.png");
    reset_->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    copy_ = new dvWidgets::AbstractButton();

    layout->addWidget(limit_);
    layout->addWidget(reset_);
    layout->addWidget(copy_);
}
