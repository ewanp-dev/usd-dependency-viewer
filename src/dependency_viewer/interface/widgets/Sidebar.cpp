#include "Sidebar.h"
#include <QVBoxLayout>

Sidebar::Sidebar() {
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    
    QVBoxLayout *layout = new QVBoxLayout();
    QSpacerItem *spacer = new QSpacerItem(0, 0, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
    layout->setSpacing(10);
    layout->setContentsMargins(10, 10, 10, 10);

    unsigned int BUTTON_WIDTH = 25;
    unsigned int BUTTON_HEIGHT = 25;

    database = new AbstractButton(
        this,
        "list.png",
        "Dependencies Database Page",
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    ); 
    
    nodegraph = new AbstractButton(
        this,
        "node.png",
        "Nodegraph Page",
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    ); 
    
    home = new AbstractButton(
        this,
        "home.png",
        "Home Page",
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    ); 
    
    settings = new AbstractButton(
        this,
        "settings.png",
        "Settings Page",
        BUTTON_WIDTH,
        BUTTON_HEIGHT
    ); 

    layout->addWidget(database);
    layout->addWidget(nodegraph);
    layout->addWidget(home);
    layout->addSpacerItem(spacer);
    layout->addWidget(settings);
    setLayout(layout);
}
