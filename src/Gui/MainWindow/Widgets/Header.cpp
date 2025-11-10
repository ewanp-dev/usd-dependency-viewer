#include "Header.h"
#include <QHBoxLayout>
#include <Gui/MainWindow/Globals.h>

// TODO Add in connections
// TODO Update hader to reflect latest interface updates

Header::Header() {
    int FIXED_HEIGHT = 40;
    setFixedHeight(FIXED_HEIGHT);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    mainLayout_ = new QHBoxLayout(this);

    setProperty("class", "WindowHeader");
}


