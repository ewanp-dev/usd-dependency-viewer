#include "Application.h"
#include <QStackedWidget>
#include <QSplitter>


DependencyViewer::DependencyViewer(QWidget *parent) {
    setWindowTitle("USD Dependency Viewer");
    setGeometry(100, 100, 1280, 720);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    // ---------------------------------------
    // WIDGETS
    
    sidebar_ = new Sidebar();
    header_ = new Header();

    // ---------------------------------------
    // PAGES SETUP
    homePage_ = new HomePage();
    
    QStackedWidget *pages = new QStackedWidget();

    pages->addWidget(homePage_);

    // ---------------------------------------
    // LAYOUTS

    QSplitter *splitter = new QSplitter(Qt::Orientation::Horizontal);
    splitter->addWidget(pages);

    QHBoxLayout *bottomLayout = new QHBoxLayout();

    bottomLayout->addWidget(sidebar_);
    bottomLayout->addWidget(splitter);

    layout->addWidget(header_);
    layout->addLayout(bottomLayout);
}

