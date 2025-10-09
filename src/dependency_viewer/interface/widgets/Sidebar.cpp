#include "Sidebar.h"
#include "../Globals.h"
#include <QVBoxLayout>
#include <iostream>

Sidebar::Sidebar() {
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    
    QVBoxLayout *layout = new QVBoxLayout();
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    unsigned int BUTTON_WIDTH = 25;
    unsigned int BUTTON_HEIGHT = 25;

    database = new AbstractButton(); 
    database->setIconFromImage(DV_ELEMENTS_DIRECTORY + "list.png");
    
    nodegraph = new AbstractButton(); 
    nodegraph->setIconFromImage(DV_ELEMENTS_DIRECTORY + "node.png");
    
    home = new AbstractButton(); 
    home->setIconFromImage(DV_ELEMENTS_DIRECTORY + "home.png");
    
    settings = new AbstractButton(); 
    settings->setIconFromImage(DV_ELEMENTS_DIRECTORY + "settings.png");

    layout->addWidget(database);
    layout->addWidget(nodegraph);
    layout->addWidget(home);
    layout->addSpacerItem(spacer);
    layout->addWidget(settings);
    setLayout(layout);
}
