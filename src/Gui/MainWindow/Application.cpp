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

DependencyViewer::DependencyViewer(const std::string& startFile, QWidget* parent)
{
    setWindowTitle("USD Depedency Viewer");
    QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
    int width = screenGeometry.width() * 0.8;
    int height = screenGeometry.height() * 0.8;
    resize(width, height);

    dependencyGraph_ = std::make_shared<UsdDependencyGraph>(startFile);

    savedWidth_ = 200;

    centralWidget_ = new QWidget(this);
    centralWidget_->setContentsMargins(2, 2, 2, 10);
    setCentralWidget(centralWidget_);

    mainLayout_ = new QVBoxLayout(centralWidget_);
    mainLayout_->setContentsMargins(0, 0, 0, 0);
    mainLayout_->setSpacing(0);

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
    footer_ = new Footer(startFile);

    // ---------------------------------------
    // PAGES SETUP
    navigationPage_ = new NavigationPage(itemDependencies_, dependencyGraph_);
    assetViewPage_ = new AssetViewPage();
    dependenciesListPage_ = new DependenciesListPage();
    homePage_ = new HomePage();
    
    QStackedWidget *pages = new QStackedWidget();

    pages->setContentsMargins(0, 0, 0, 0);
    pages->addWidget(homePage_);
    pages->addWidget(navigationPage_);
    pages->addWidget(dependenciesListPage_);
    pages->addWidget(assetViewPage_);

    connect(header_->homeButton(), &dvWidgets::AbstractButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(homePage_);
    });

    connect(header_->visualizationButton(), &dvWidgets::AbstractButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(navigationPage_);
    });

    connect(header_->dependenciesButton(), &dvWidgets::AbstractButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(dependenciesListPage_);
    });

    connect(header_->assetButton(), &dvWidgets::AbstractButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(assetViewPage_);
    });

    // ---------------------------------------
    // LAYOUT

    QSplitter *splitter = new QSplitter(Qt::Orientation::Horizontal);
    splitter->addWidget(treeWidget_);
    splitter->addWidget(pages);
    splitter->setSizes({400, 400});

    QHBoxLayout *bottomLayout = new QHBoxLayout();

    bottomLayout->addWidget(splitter);

    mainLayout_->addWidget(header_);
    mainLayout_->addLayout(bottomLayout);
    mainLayout_->addWidget(footer_);

    // ---------------------------------------
    // SIGNALS

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

    while(!in.atEnd()) 
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

void DependencyViewer::expandDropdown_(bool checked) 
{
    if (checked) 
    {
        treeWidget_->show();
        QPropertyAnimation *anim = new QPropertyAnimation(treeWidget_, "maximumWidth"); 
        anim->setDuration(150);
        anim->setStartValue(0);
        anim->setEndValue(savedWidth_);
        connect(anim, &QPropertyAnimation::finished, this, [this]() {
            treeWidget_->setMaximumWidth(QWIDGETSIZE_MAX);
        });
        anim->start();
    } 
    else 
    {
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

