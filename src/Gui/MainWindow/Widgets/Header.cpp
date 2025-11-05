#include "Header.h"
#include <QHBoxLayout>
#include <Gui/MainWindow/Globals.h>

// TODO Add in connections

Header::Header() {
    int FIXED_HEIGHT = 40;
    setFixedHeight(FIXED_HEIGHT);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    // layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(10);

    expand = new AbstractButton();
    expand->setIconFromImage(":icons/sidebar.png");

    // TODO: Convert this to a QLineEdit or something similar to Githubs search function
    search = new AbstractButton();
    search->setIconFromImage(":/icons/search.png");

    expand->setCheckable(true);

    layout->addWidget(expand);
    layout->addStretch();
    layout->addWidget(search);

    setProperty("class", "WindowHeader");
}


