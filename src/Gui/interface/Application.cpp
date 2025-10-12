#include "Application.h"
#include "widgets/Search.h"
#include <QStackedWidget>
#include <QSplitter>
#include <QObject>
#include <QPropertyAnimation>
#include <iostream>
#include <vector>
#include <QFile>
#include <QDir>
#include <QApplication>

DependencyViewer::DependencyViewer(QWidget *parent) {
    setWindowTitle("USD Dependency Viewer");
    setGeometry(100, 100, 1280, 720);

    savedWidth_ = 200;

    QWidget *centralWidget = new QWidget(this);
    centralWidget->setContentsMargins(0, 0, 0, 0);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);
    layout->setContentsMargins(0, 0, 0, 0);

    std::vector<std::string> deps = {"Hello", "World"};
    itemDependencies_ = deps;
    initStyleSheet();

    // ---------------------------------------
    // WIDGETS
    
    sidebar_ = new Sidebar();
    header_ = new Header();
    searchWidget_ = new SearchWidget(itemDependencies_);
    settingsWidget_ = new SettingsWidget(this);
    treeWidget_ = new DependenciesTreeWidget();
    treeWidget_->hide();

    // ---------------------------------------
    // PAGES SETUP
    databasePage_ = new DatabasePage(itemDependencies_);
    nodegraphPage_ = new NodegraphPage();
    homePage_ = new HomePage();
    
    QStackedWidget *pages = new QStackedWidget();

    pages->addWidget(homePage_);
    pages->addWidget(databasePage_);
    pages->addWidget(nodegraphPage_);

    // NOTE: I might move these connections to a function inside of the sidebar class
    connect(sidebar_->database, &QPushButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(databasePage_);
    });

    connect(sidebar_->nodegraph, &QPushButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(nodegraphPage_);
    });

    connect(sidebar_->home, &QPushButton::clicked, this, [this, pages]() {
        pages->setCurrentWidget(homePage_);
    });

    // ---------------------------------------
    // LAYOUT

    QSplitter *splitter = new QSplitter(Qt::Orientation::Horizontal);
    splitter->addWidget(treeWidget_);
    splitter->addWidget(pages);
    splitter->setSizes({90, 600});

    QHBoxLayout *bottomLayout = new QHBoxLayout();

    bottomLayout->addWidget(sidebar_);
    bottomLayout->addWidget(splitter);

    layout->addWidget(header_);
    layout->addLayout(bottomLayout);

    // ---------------------------------------
    // SIGNALS

    connect(header_->expand, &AbstractButton::clicked, this, [this] {
        expandDropdown_(
            header_->expand->isChecked()
        );
    });

    connect(header_->search, &QPushButton::clicked, this, [this]() {
        showFloatingWidget_(
            searchWidget_
        );
    });

    connect(sidebar_->settings, &QPushButton::clicked, this, [this]() {
        showFloatingWidget_(
            settingsWidget_
        );
    });
}

void DependencyViewer::initStyleSheet()
{
    qDebug() << "Current working directory: " << QDir::currentPath();
    QFile file(":/styles/style.qss");
    QFile colorScheme(":/styles/default-color-scheme.qss");
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

        qApp->setStyleSheet(stylesheet);
    }
    else
    {
        qDebug() << "Cannot read file :/styles/style.qss\n";
    }

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

