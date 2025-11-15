#include "Viewport.h"

Viewport::Viewport(QWidget* parent)
{
    mainLayout_ = new QVBoxLayout(this);

    label_ = new QLabel("Viewport Page");

    mainLayout_->addWidget(label_);
}

