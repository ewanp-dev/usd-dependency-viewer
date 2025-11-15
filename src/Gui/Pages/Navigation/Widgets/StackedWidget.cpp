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

    buttonsLayout_ = new QHBoxLayout();
    buttonsLayout_->setSpacing(0);

    // NOTE:
    //  - Might need to create a initButton class to avoid boilerplate code

    nodegraphButton_ = initButton("Nodegraph", 0);
    nodegraphButton_->setChecked(true); 
    nodegraphButton_->setProperty("class", "PagesButtonChecked");

    viewportButton_ = initButton("3D Viewport", 1);
    filePropertiesButton_ = initButton("File Properties", 2);
    usdInspectionButton_ = initButton("USD Inspect", 3);

    buttonsLayout_->addWidget(nodegraphButton_);
    buttonsLayout_->addWidget(viewportButton_);
    buttonsLayout_->addWidget(filePropertiesButton_);
    buttonsLayout_->addWidget(usdInspectionButton_);

    initPages();

    mainLayout_->addLayout(buttonsLayout_);
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
    stackedPages_ = new QStackedWidget();

    nodegraph_ = new Nodegraph(dependencies_);
    viewport_ = new Viewport();

    stackedPages_->addWidget(nodegraph_);
    stackedPages_->addWidget(viewport_);

    // TODO:
    //  - Add in page switching connections
}

dvWidgets::AbstractButton* NavigationStackedWidget::initButton(const std::string& text, int index)
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    buttons_.push_back(button);

    button->setText(text.c_str());
    button->setCheckable(true);
    button->setChecked(false);
    button->setProperty("class", "PagesButtonUnchecked");

    connect(button, &dvWidgets::AbstractButton::clicked, this, [this, button, index] {
        onButtonClicked(button, index);
    });

    return button;
}

void NavigationStackedWidget::onButtonClicked(dvWidgets::AbstractButton* button, int index)
{
    // TODO:
    //  - Uncheck all other pages when a new button is checked

    stackedPages_->setCurrentIndex(index);

    for (dvWidgets::AbstractButton* btn : buttons_)
    {
        if (btn == button)
        {
            btn->setChecked(true);
            btn->setStyleSheet("background-color: #749E94");
        } 
        else
        {
            btn->setChecked(false);
            btn->setStyleSheet("background-color: #171717");
        }
    }
}

