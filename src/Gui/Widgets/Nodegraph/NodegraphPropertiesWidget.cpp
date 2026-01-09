#include "NodegraphPropertiesWidget.h"

#include <QStyleFactory>

NodegraphPropertiesWidget::NodegraphPropertiesWidget(QWidget* parent)
    : QWidget(parent)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    setAttribute(Qt::WA_StyledBackground, true);
    setAttribute(Qt::WA_ShowWithoutActivating, true);
    setFixedSize(250, 120);

    setObjectName("NodegraphPropertiesWidget");
    setStyleSheet(
        "#NodegraphPropertiesWidget {"
        "   background-color: #262626;"
        "   border-radius: 4px;"
        "   padding: 6px;"
        "}"
    );

    selectionEvents_ = {
        showDependencies_,
        allowHoverEvents_,
        dimUnselectedNodes_
    };

    mainLayout_ = new QVBoxLayout();

    header_ = new QLabel("Nodegraph Properties");
    QFont f = header_->font();
    f.setBold(true);
    f.setPointSize(10);
    header_->setFont(f);
    header_->setStyleSheet("color: #799E94;");

    QHBoxLayout* dependenciesLayout = new QHBoxLayout();
    showAllDependenciesLabel_ = new QLabel("Show all dependencies: ");
    showAllDependenciesButton_ = initButton(0);
    dependenciesLayout->addWidget(showAllDependenciesLabel_);
    dependenciesLayout->addStretch();
    dependenciesLayout->addWidget(showAllDependenciesButton_);

    connect(showAllDependenciesButton_, &dvWidgets::AbstractButton::clicked, this, [this] () {
        
    });

    QHBoxLayout* hoverEventsLayout = new QHBoxLayout();
    allowHoverEventsLabel_ = new QLabel("Allow hover events: ");
    allowHoverEventsButton_ = initButton(1);
    hoverEventsLayout->addWidget(allowHoverEventsLabel_);
    hoverEventsLayout->addStretch();
    hoverEventsLayout->addWidget(allowHoverEventsButton_);

    connect(allowHoverEventsButton_, &dvWidgets::AbstractButton::clicked, this, [this] () {
        
    });

    QHBoxLayout* dimLayout = new QHBoxLayout();
    dimUnselectedNodesLabel_ = new QLabel("Dim unselected nodes: ");
    dimUnselectedNodesButton_ = initButton(2);
    dimLayout->addWidget(dimUnselectedNodesLabel_);
    dimLayout->addStretch();
    dimLayout->addWidget(dimUnselectedNodesButton_);

    connect(dimUnselectedNodesButton_, &dvWidgets::AbstractButton::clicked, this, [this] () {
        
    });

    mainLayout_->addWidget(header_);
    mainLayout_->addSpacing(8);
    mainLayout_->addLayout(dependenciesLayout);
    mainLayout_->addLayout(hoverEventsLayout);
    mainLayout_->addLayout(dimLayout);
    mainLayout_->addStretch();
    setLayout(mainLayout_);
}

void NodegraphPropertiesWidget::leaveEvent(QEvent* event)
{
    QWidget::leaveEvent(event);
}

void NodegraphPropertiesWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    } else
    {
        QWidget::keyPressEvent(event);
    }
}

dvWidgets::AbstractButton* NodegraphPropertiesWidget::initButton(int num)
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setFixedSize(20, 20);
    button->enableHoverEvent(false);
    button->setStyleSheet(
    "QPushButton {"
    "   background-color: #262626;"
    "   border: 1px solid #171717;"
    "}"
    "QPushButton:hover {"
    "   background-color: #799E94;"
    "}"
    "QPushButton:checked {"
    "   background-color: #799E94;"
    "}"
    );

    connect(button, &dvWidgets::AbstractButton::clicked, this, [this, button, num] () {
        if (button->isChecked())
        {
            selectionEvents_[num] = true;
        } else
        {
            selectionEvents_[num] = false;
        }
    });

    return button;
}
