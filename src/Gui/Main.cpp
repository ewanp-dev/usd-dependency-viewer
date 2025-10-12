#include "interface/Application.h"
#include "interface/Globals.h"
#include <QApplication>
#include <QFontDatabase>
#include <QFont>
#include <QString>
#include <QFile>
#include <QDir>
#include <iostream>
#include <unordered_map>

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
    QFile file(":/styles/style.qss");
    QFile colorScheme(":/styles/default-color-scheme.qss");
    if (!colorScheme.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "color sheme cannot be opened for read.";
        return 1;
    }
    QTextStream in(&colorScheme);

    std::unordered_map<QString, QString> styleVariables;
    while(!in.atEnd()) {
        QString line = in.readLine();    
        if(line.length()<1) continue;
        if(!line.startsWith('@')) continue;

        QStringList fields = line.split("=");    
        if(fields.length() != 2)
        {
            qDebug() << "Skipping parsing of line: " << line << "\n";
            continue;
        }
        std::cout << "line: " << line.toStdString() << "\n";
        QString variableName = fields.at(0).trimmed();
        QString variableValue = fields.at(1).trimmed();

        if(variableValue.endsWith(';'))
        {
            variableValue.chop(1);
        }
        
        styleVariables.emplace(variableName, variableValue);

        std::cout << "variableName: " << variableName.toStdString() << "\n";
        std::cout << "variableName: " << variableValue.toStdString() << "\n";
    }

    colorScheme.close();

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Global style opened for read" << '\n';
        QString stylesheet = file.readAll();
        for(auto i : styleVariables)
        {
            stylesheet.replace(i.first, i.second);
        }
        app.setStyleSheet(stylesheet);
        file.close();
    }
    else
    {
        qDebug() << "Cannot read file :/styles/style.qss\n";
    }

    DependencyViewer* viewer = new DependencyViewer();

    viewer->show();

    return app.exec();
}
