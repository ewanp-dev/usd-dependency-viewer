#include <Gui/MainWindow/Application.h>
#include <Gui/MainWindow/Globals.h>
#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>
#include <QFile>
#include <QDir>

int main (int argc, char **argv) {
    QApplication app (argc, argv);
    QApplication::setCursorFlashTime(0);

    DependencyViewer* viewer = new DependencyViewer();

    viewer->show();

    return app.exec();
}
