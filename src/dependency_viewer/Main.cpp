#include "interface/Application.h"
#include "interface/Globals.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>

int main (int argc, char **argv) {
    QApplication app (argc, argv);
    
    std::string fontName = DV_ELEMENTS_DIRECTORY + "FiraCodeNerdFontMono-Regular.ttf";
    int id = QFontDatabase::addApplicationFont(fontName.c_str());
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(family, 10);
    app.setFont(font);
    DependencyViewer* viewer = new DependencyViewer();

    viewer->show();

    return app.exec();
}
