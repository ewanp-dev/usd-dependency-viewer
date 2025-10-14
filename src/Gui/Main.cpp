#include "interface/Application.h"
#include "interface/Globals.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>
#include <QFile>
#include <QDir>
#include "Core/DependencyEvaluation.h"

int main (int argc, char **argv) {
    QApplication app (argc, argv);
    QApplication::setCursorFlashTime(0);

    DependencyViewer* viewer = new DependencyViewer();

    viewer->show();

    UsdDependencyGraph("/home/parker/Downloads/ALab-2.2.0/ALab/entry.usda");

    return app.exec();
}
