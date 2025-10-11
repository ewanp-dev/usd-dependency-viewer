#include "interface/Application.h"
#include "interface/Globals.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>
#include <QFile>
#include <QDir>
#include <iostream>

int main (int argc, char **argv) {
    QApplication app (argc, argv);
    QApplication::setCursorFlashTime(0);

    // NOTE: Setting embedded font
    std::string fontName = ":/fonts/FiraCodeNerdFontMono-Regular.ttf";
    int id = QFontDatabase::addApplicationFont(fontName.c_str());
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(family, 10);
    app.setFont(font);

    // NOTE: Setting embedded .qss stylesheet
    qDebug() << "Current working directory: " << QDir::currentPath();
    QFile file("src/dependency_viewer/interface/elements/styles/style.qss");
    if (file.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "File is found " << '\n';
        QString stylesheet = file.readAll();
        app.setStyleSheet(stylesheet);
    }

    DependencyViewer* viewer = new DependencyViewer();

    viewer->show();

    return app.exec();
}
