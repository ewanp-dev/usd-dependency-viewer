#include "Application.h"

#include <QObject>
#include <vector>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QFontDatabase>

#include <Gui/Widgets/Search.h>

DependencyViewer::DependencyViewer(const std::string& startFile, QWidget* parent) 
    : startFile_(startFile)
{
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    int width            = screenGeometry.width() * 0.8;
    int height           = screenGeometry.height() * 0.8;

    resize(width, height);
    setWindowTitle("USD Dependency Viewer");

    dependencyGraph_ = std::make_shared<UsdDependencyGraph>(startFile_);
    std::vector<std::string> flattenedDependencies_ = dependencyGraph_->getFlattenedPaths();
    numDependencies_ = flattenedDependencies_.size();

    centralWidget_ = new QWidget(this);
    centralWidget_->setContentsMargins(2, 2, 2, 10);
    setCentralWidget(centralWidget_);

    mainLayout_ = new QVBoxLayout(centralWidget_);
    mainLayout_->setContentsMargins(0, 0, 0, 0);
    mainLayout_->setSpacing(0);

    std::vector<std::string> deps = {};
    itemDependencies_             = deps;

    initStyleSheet();
    initFonts();
    initWidgets(flattenedDependencies_);
}

void DependencyViewer::initStyleSheet()
{
    QFile file(":/styles/style.qss");
    QFile colorScheme(":/styles/darkmode-color-scheme.qss");

    if (!colorScheme.open(QFile::ReadOnly | QFile::Text)) 
    {
        qDebug() << "color sheme cannot be opened for read.";
        return;
    }

    QTextStream in(&colorScheme);
    std::unordered_map<QString, QString> styleVariables;

    while (!in.atEnd()) 
    {
        QString line = in.readLine();    

        if (line.length()<1) continue;
        if (!line.startsWith('@')) continue;

        QStringList fields = line.split("=");    
        if (fields.length() != 2)
        {
            qDebug() << "Skipping parsing of line: " << line << "\n";
            continue;
        }

        QString variableName = fields.at(0).trimmed();
        QString variableValue = fields.at(1).trimmed();

        if (variableValue.endsWith(';'))
        {
            variableValue.chop(1);
        }
        
        styleVariables.emplace(variableName, variableValue);
    }

    colorScheme.close();

    if (file.open(QFile::ReadOnly | QFile::Text)) 
    {
        QString stylesheet = file.readAll();
        
        for (auto i : styleVariables)
        {
            stylesheet.replace(i.first, i.second);
        }

        qApp->setStyleSheet(stylesheet);
    } else
    {
        qDebug() << "Cannot read file :/styles/style.qss\n";
    }

}

void DependencyViewer::initFonts()
{
    std::string fontName = ":/fonts/JetBrainsMonoNerdFont-Regular.ttf";
    int id               = QFontDatabase::addApplicationFont(fontName.c_str());
    QString family       = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font           = QFont(family, 10);
    
    font.setStyleStrategy(QFont::PreferAntialias);
    qApp->setFont(font);
}

void DependencyViewer::initWidgets(std::vector<std::string> dependencies)
{
    std::cout << numDependencies_ << '\n';
    header_ = new Header();
    footer_ = new Footer(startFile_, numDependencies_);
    navigationPage_       = new NavigationPage(itemDependencies_, dependencyGraph_);

    mainLayout_->addWidget(header_);
    mainLayout_->addWidget(navigationPage_);
    mainLayout_->addWidget(footer_);
}

void DependencyViewer::showFloatingWidget(QWidget* widget) 
{
    if (widget == nullptr) 
    {
        return;
    }

    QWidget* parent = widget->parentWidget();

    if (parent) 
    {
        QRect parentGeom = parent->geometry();

        int x = parentGeom.x() + (parentGeom.width() - widget->width()) / 2;
        int y = parentGeom.y() + (parentGeom.height() - widget->height()) / 2;

        widget->move(QPoint(x, y));

    }

    widget->show();
}
