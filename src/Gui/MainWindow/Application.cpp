#include "Application.h"
#include <QStackedWidget>
#include <QSplitter>
#include <QObject>
#include <QPropertyAnimation>
#include <vector>
#include <QFile>
#include <QDir>
#include <QApplication>
#include <QFontDatabase>
#include <Gui/MainWindow/Widgets/Search.h>

DependencyViewer::DependencyViewer(std::string startFile, QWidget *parent)
{
    setWindowTitle("USD Depedency Viewer");
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    int width = screenGeometry.width() * 0.8;
    int height = screenGeometry.height() * 0.8;
    resize(width, height);

    // setGeometry(100, 100, 1280, 720);

    dependencyGraph_ = std::make_shared<UsdDependencyGraph>(startFile);

    savedWidth_ = 200;

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    std::vector<std::string> deps = {"Hello", "World"};
    itemDependencies_ = deps;

    initStyleSheet();
    initFonts();

    // ---------------------------------------
    // WIDGETS
    
    header_ = new Header();
    searchWidget_ = new SearchWidget(itemDependencies_);
    settingsWidget_ = new SettingsWidget(this);
    treeWidget_ = new DependenciesTreeWidget();
    treeWidget_->hide();

    // ---------------------------------------
    // PAGES SETUP
    navPage_ = new NavigationPage(itemDependencies_, dependencyGraph_);
    homePage_ = new HomePage();
    
    QStackedWidget *pages = new QStackedWidget();

    pages->addWidget(homePage_);
    // BUG: navPage is havving horizontal expanding issues
    // pages->addWidget(navPage_);

    // ---------------------------------------
    // LAYOUT

    QSplitter *splitter = new QSplitter(Qt::Orientation::Horizontal);
    splitter->addWidget(treeWidget_);
    splitter->addWidget(pages);
    splitter->setSizes({90, 600});

    QHBoxLayout *bottomLayout = new QHBoxLayout();

    bottomLayout->addWidget(splitter);

    layout->addWidget(header_);
    layout->addLayout(bottomLayout);

    // ---------------------------------------
    // SIGNALS

}

void DependencyViewer::initStyleSheet()
{
    qDebug() << "Current working directory: " << QDir::currentPath();
    QFile file(":/styles/style.qss");
    QFile colorScheme(":/styles/darkmode-color-scheme.qss");
    if (!colorScheme.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "color sheme cannot be opened for read.";
        return;
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
        QString variableName = fields.at(0).trimmed();
        QString variableValue = fields.at(1).trimmed();

        if(variableValue.endsWith(';'))
        {
            variableValue.chop(1);
        }
        
        styleVariables.emplace(variableName, variableValue);
    }

    colorScheme.close();

    if (file.open(QFile::ReadOnly | QFile::Text)) {
        QString stylesheet = file.readAll();
        for(auto i : styleVariables)
        {
            stylesheet.replace(i.first, i.second);
        }

        qApp->setStyleSheet(stylesheet);
    }
    else
    {
        qDebug() << "Cannot read file :/styles/style.qss\n";
    }

}

void DependencyViewer::initFonts()
{
    std::string fontName = ":/fonts/JetBrainsMonoNerdFont-Regular.ttf";
    int id = QFontDatabase::addApplicationFont(fontName.c_str());
    QString family = QFontDatabase::applicationFontFamilies(id).at(0);
    QFont font = QFont(family, 10);
    qApp->setFont(font);
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

