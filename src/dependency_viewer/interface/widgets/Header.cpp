#include "Header.h"
#include <QHBoxLayout>

Header::Header() {
    int FIXED_HEIGHT = 40;
    setFixedHeight(FIXED_HEIGHT);
    setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);

    QHBoxLayout *layout = new QHBoxLayout(this);
    layout->setContentsMargins(10, 0, 10, 0);
    layout->setSpacing(10);

    expand = new AbstractButton(
        this,
        "sidebar.png",
        "Open and close dropdown view",
        25,
        25
    );

    search = new AbstractButton(
        this,
        "search.png",
        "Search for dependencies",
        25,
        25
    );

    expand->setCheckable(true);

    layout->addWidget(expand, Qt::AlignmentFlag::AlignLeft);
    layout->addWidget(search, Qt::AlignmentFlag::AlignRight);
}


