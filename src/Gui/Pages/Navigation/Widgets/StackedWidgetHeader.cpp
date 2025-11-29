#include "StackedWidgetHeader.h"

#include <Gui/Widgets/AbstractWidgetUtils.h>

StackedWidgetHeader::StackedWidgetHeader(QWidget* parent)
{
    // setFixedHeight(52);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Maximum);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    setProperty("class", "standardWidget");
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet(
        "border-top-left-radius: 4px;"
        "border-top-right-radius: 4px;"
    );

    mainLayout_    = new QHBoxLayout(this);
    mainLayout_->setContentsMargins(12, 12, 12, 12);

    nodegraphButton_ = initButton("Nodegraph");
    nodegraphButton_->setChecked(true); // Nodegraph is first selected by default
    nodegraphButton_->setStyleSheet(
        "background-color: #799E94;"
        "border: none;"
        "padding: 8px 8px;"
    );

    viewportButton_ = initButton("3D Viewport");
    filePropertiesButton_ = initButton("File Properties");
    usdInspectionButton_ = initButton("USD Inspect");

    mainLayout_->addWidget(nodegraphButton_);
    mainLayout_->addSpacing(8);
    mainLayout_->addWidget(viewportButton_);
    mainLayout_->addSpacing(8);
    mainLayout_->addWidget(filePropertiesButton_);
    mainLayout_->addSpacing(8);
    mainLayout_->addWidget(usdInspectionButton_);

}

dvWidgets::AbstractButton* StackedWidgetHeader::initButton(const std::string& text)
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setFixedHeight(30);
    button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    button->adjustSize();
    button->setText(text.c_str());
    button->setCursor(Qt::PointingHandCursor);

    headerButtons_.push_back(button);

    connect(button, &dvWidgets::AbstractButton::clicked, this, [this, button]() {
        dvWidgets::AbstractWidgetUtils::setSelectedButtonItem(headerButtons_, button); 
    });

    return button;
}

dvWidgets::AbstractButton* StackedWidgetHeader::nodegraphPageButton()
{
    return nodegraphButton_;
}

dvWidgets::AbstractButton* StackedWidgetHeader::viewportPageButton()
{
    return viewportButton_;
}

dvWidgets::AbstractButton* StackedWidgetHeader::filePropertiesPageButton()
{
    return filePropertiesButton_;
}

dvWidgets::AbstractButton* StackedWidgetHeader::usdInspectionPageButton()
{
    return usdInspectionButton_;
}
