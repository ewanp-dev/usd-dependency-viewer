#include "interface/Application.h"
#include <QApplication>

int main (int argc, char **argv) {
    QApplication app (argc, argv);

    DependencyViewer* viewer = new DependencyViewer();

    viewer->show();

    return app.exec();
}
