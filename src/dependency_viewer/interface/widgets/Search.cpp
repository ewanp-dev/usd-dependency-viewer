#include "Search.h"
#include "../Globals.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <Qt>

SearchWidget::SearchWidget(std::vector<std::string> dependencies, QWidget* parent) {
    setWindowFlags(Qt::WindowFlags(Qt::FramelessWindowHint | Qt::Dialog));
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    setFocusPolicy(Qt::FocusPolicy::ClickFocus);
    setFixedSize(500, 500);

    // WIDGETS
    searchBar_ = new QLineEdit();
    results_ = new QListWidget();
    exitButton_ = new AbstractButton();
    exitButton_->setIconFromImage(":icons/list.png");

    searchBar_->setPlaceholderText("> Search for dependency...");
    searchBar_->setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    searchBar_->setFixedHeight(DV_BUTTON_HEIGHT);

    QVBoxLayout* layout = new QVBoxLayout(this);
    QHBoxLayout* topLayout = new QHBoxLayout();

    topLayout->addWidget(searchBar_);
    topLayout->addWidget(exitButton_);

    layout->addLayout(topLayout);
    layout->addWidget(results_);

    connect(exitButton_, &AbstractButton::clicked, this, &QWidget::close);

    dependencies_ = dependencies; 

    populateDefaultList();

    searchBar_->setStyleSheet(R"(
        QLineEdit {
            background-color: rgb(60, 60, 60);
            color: rgb(210, 210, 210);
            padding-left: 6px;
            padding-right: 6px;
            border-radius: 0px;
        }
    )");

    results_->setStyleSheet(R"(
        QListWidget {
            background-transparent;
            color: rgb(210, 210, 210);
            padding: 6px 6px;
        }
    )");

    setStyleSheet(R"(
        QWidget {
            background-color: rgb(12, 12, 12);
        }
    )");
}

void SearchWidget::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key::Key_Escape) {
        close();
    } else {
        QWidget::keyPressEvent(event);
    }
}

void SearchWidget::populateDefaultList() {
    for (size_t i = 0; i < dependencies_.size(); i++) 
    {
        if (i > 10) 
            break;
        results_->addItem(dependencies_[i].c_str());
    }
}
