#include "StackedWidget.h"

// Class containing the different widgets on the Navigation page,

// NOTE:
//  - Fix contents margins
//  - Externalise signals
//  - Button stylesheet sticks when switching page

NavigationStackedWidget::NavigationStackedWidget(const std::vector<std::string>& dependencies, QWidget* parent)
    : dependencies_(dependencies)
{
    // NOTE:
    //  - Move dependencies_ to a better position
    //    it needs to become a global variable or easily
    //    accessible

    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->setSpacing(0);

    header_ = new StackedWidgetHeader();

    initPages();

    mainLayout_->addWidget(header_);
    mainLayout_->addWidget(stackedPages_);
}

Nodegraph* NavigationStackedWidget::nodegraph()
{
    // This should make it easier to access the nodegraph externally
    // rather than creating multiple instances of dependencies

    // TODO:
    //  - Move nodegraph dependencies to a setter rather than
    //    having it as an argument

    return nodegraph_;
}

void NavigationStackedWidget::initPages()
{
    // NOTE:
    //
    // Need to change the page variable names so they
    // all match the same convention

    stackedPages_ = new QStackedWidget();
    nodegraph_    = new Nodegraph(dependencies_);
    viewport_     = new Viewport();
    filePropertiesPage_ = new FilePropertiesPage();
    usdInspectionPage_ = new UsdInspectionPage();

    stackedPages_->addWidget(nodegraph_);
    stackedPages_->addWidget(viewport_);
    stackedPages_->addWidget(filePropertiesPage_);
    stackedPages_->addWidget(usdInspectionPage_);

    connect(header_->nodegraphPageButton(), &dvWidgets::AbstractButton::clicked, this, [this]() {
        stackedPages_->setCurrentWidget(nodegraph_);
    });

    connect(header_->viewportPageButton(), &dvWidgets::AbstractButton::clicked, this, [this]() {
        stackedPages_->setCurrentWidget(viewport_);
    });

    connect(header_->filePropertiesPageButton(), &dvWidgets::AbstractButton::clicked, this, [this]() {
        stackedPages_->setCurrentWidget(filePropertiesPage_);
    });

    connect(header_->usdInspectionPageButton(), &dvWidgets::AbstractButton::clicked, this, [this]() {
        stackedPages_->setCurrentWidget(usdInspectionPage_);
    });
}

