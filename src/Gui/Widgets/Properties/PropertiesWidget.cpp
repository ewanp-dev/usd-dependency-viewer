#include "PropertiesWidget.h"

PropertiesWidget::PropertiesWidget(QWidget* parent)
{
    setMinimumWidth(60);
    setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
    setContentsMargins(0, 0, 0, 0);

    QWidget* container = new QWidget(this);
    QVBoxLayout* layout = new QVBoxLayout(this);
    mainLayout_ = new QVBoxLayout(container);

    layout->addWidget(container);
    layout->setContentsMargins(0, 8, 8, 0);
    container->setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    container->setProperty("class", "standardWidget");
    container->setStyleSheet(
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
    );
    container->setContentsMargins(12, 12, 12, 12);
}
