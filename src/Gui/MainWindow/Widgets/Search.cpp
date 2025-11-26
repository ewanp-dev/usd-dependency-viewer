#include "Search.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <Qt>
#include <Gui/MainWindow/Globals.h>

SearchWidget::SearchWidget(std::vector<std::string> dependencies, QWidget* parent) {
    setWindowFlags(Qt::WindowFlags(Qt::FramelessWindowHint | Qt::Dialog));
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    setProperty("class", "SearchWidget");
    setFixedSize(500, 500);

    // WIDGETS
    searchBar_  = new QLineEdit();
    results_    = new QListWidget();
    exitButton_ = new dvWidgets::AbstractButton();
    exitButton_->setIconFromImage(":icons/list.png");

    searchBar_->setPlaceholderText("> Search for dependency...");
    searchBar_->setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    searchBar_->setFixedHeight(DV_BUTTON_HEIGHT);

    QVBoxLayout* layout    = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();

    topLayout->addWidget(searchBar_);
    topLayout->addWidget(exitButton_);

    layout->addLayout(topLayout);
    layout->addWidget(results_);

    connect(exitButton_, &dvWidgets::AbstractButton::clicked, this, &QWidget::close);

    dependencies_ = dependencies; 

    populateDefaultList();

    searchBar_->setProperty("class", "SearchBar");
}

void SearchWidget::keyPressEvent(QKeyEvent *event) 
{
    if (event->key() == Qt::Key::Key_Escape) 
    {
        close();
    } else 
    {
        QWidget::keyPressEvent(event);
    }
}

void SearchWidget::populateDefaultList() 
{
    for (size_t i = 0; i < dependencies_.size(); i++) 
    {
        if (i > 10) 
            break;
        
        results_->addItem(dependencies_[i].c_str());
    }
}
