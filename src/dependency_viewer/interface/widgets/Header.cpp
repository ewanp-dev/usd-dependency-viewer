#include "Header.h"
#include "../Globals.h"
#include <QHBoxLayout>

Header::Header() {
    int FIXED_HEIGHT = 40;
    setFixedHeight(FIXED_HEIGHT);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    // layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(10);

    expand = new AbstractButton();
    expand->setIconFromImage(DV_ELEMENTS_DIRECTORY + "sidebar.png");

    // TODO: Convert this to a QLineEdit or something similar to Githubs search function
    search = new AbstractButton();
    search->setIconFromImage(DV_ELEMENTS_DIRECTORY + "search.png");

    expand->setCheckable(true);

    layout->addWidget(expand);
    layout->addStretch();
    layout->addWidget(search);

    setStyleSheet(R"(
        QWidget {
            background-color: rgb(20, 20, 20);
        }
    )");
}


