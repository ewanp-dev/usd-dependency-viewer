#include "Application.h"
#include "widgets/Search.h"
#include <QStackedWidget>
#include <QSplitter>
#include <QObject>
#include <QPropertyAnimation>
#include <iostream>
#include <vector>

DependencyViewer::DependencyViewer(QWidget *parent) {
    setWindowTitle("USD Dependency Viewer");
    setGeometry(100, 100, 1280, 720);

    savedWidth_ = 200;

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    std::vector<std::string> deps = {"Hello", "World"};
    itemDependencies_ = deps;
    // ---------------------------------------
    // WIDGETS
    
    sidebar_ = new Sidebar();
    header_ = new Header();
    searchWidget_ = new SearchWidget(itemDependencies_);
    settingsWidget_ = new SettingsWidget();
    treeWidget_ = new DependenciesTreeWidget();
    treeWidget_->hide();

    // ---------------------------------------
    // PAGES SETUP
    databasePage_ = new DatabasePage(itemDependencies_);
    nodegraphPage_ = new NodegraphPage();
    homePage_ = new HomePage();
    
    QStackedWidget *pages = new QStackedWidget();

    pages->addWidget(homePage_);
    pages->addWidget(databasePage_);
    pages->addWidget(nodegraphPage_);

    // NOTE: I might move these connections to a function inside of the sidebar class
    connect(sidebar_->database, &QPushButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(databasePage_);
    });

    connect(sidebar_->nodegraph, &QPushButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(nodegraphPage_);
    });

    connect(sidebar_->home, &QPushButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(homePage_);
    });

    // ---------------------------------------
    // LAYOUT

    QSplitter *splitter = new QSplitter(Qt::Orientation::Horizontal);
    splitter->addWidget(treeWidget_);
    splitter->addWidget(pages);
    splitter->setSizes({90, 600});

    QHBoxLayout *bottomLayout = new QHBoxLayout();

    bottomLayout->addWidget(sidebar_);
    bottomLayout->addWidget(splitter);

    layout->addWidget(header_);
    layout->addLayout(bottomLayout);

    // ---------------------------------------
    // SIGNALS

    connect(header_->expand, &AbstractButton::clicked, this, [this] {
        expandDropdown_(
            header_->expand->isChecked()
        );
    });

    connect(header_->search, &QPushButton::clicked, this, [this]() {
        showFloatingWidget_(
            searchWidget_
        );
    });

    connect(sidebar_->settings, &QPushButton::clicked, this, [this]() {
        showFloatingWidget_(
            settingsWidget_
        );
    });
}

void DependencyViewer::showFloatingWidget_(QWidget* widget) {
    if (widget == nullptr) {
        return;
    }

    QWidget* parent = widget->parentWidget();
    if (parent) {
        QRect parentGeom = parent->geometry();

        int x = parentGeom.x() + (parentGeom.width() - widget->width()) / 2;
        int y = parentGeom.y() + (parentGeom.height() - widget->height()) / 2;

        widget->move(QPoint(x, y));

    }
    widget->show();
}

void DependencyViewer::expandDropdown_(bool checked) {
    if (checked) {
        treeWidget_->show();
        QPropertyAnimation *anim = new QPropertyAnimation(treeWidget_, "maximumWidth"); 
        anim->setDuration(150);
        anim->setStartValue(0);
        anim->setEndValue(savedWidth_);
        connect(anim, &QPropertyAnimation::finished, this, [this]() {
            treeWidget_->setMaximumWidth(QWIDGETSIZE_MAX);
        });
        anim->start();
    } else {
        int startWidth = treeWidget_->width();
        savedWidth_ = startWidth;
        QPropertyAnimation *anim = new QPropertyAnimation(treeWidget_, "maximumWidth"); 
        anim->setDuration(150);
        anim->setStartValue(startWidth);
        anim->setEndValue(0);
        connect(anim, &QPropertyAnimation::finished, this, [this]() {
            treeWidget_->hide();
            treeWidget_->setMaximumWidth(QWIDGETSIZE_MAX);
        });
        anim->start();
    }
}

