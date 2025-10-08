#include "Application.h"
#include "AbstractButton.h"
#include <QStackedWidget>


DependencyViewer::DependencyViewer(QWidget *parent) {
    setWindowTitle("USD Dependency Viewer");
    setGeometry(100, 100, 1280, 720);

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    AbstractButton *testButton = new AbstractButton(this, "button.png", "Click to test", 10, 10);
    layout->addWidget(testButton);

    // PAGES SETUP
    QStackedWidget *pages = new QStackedWidget();
}

