#pragma once

#include <QWidget>
#include <Gui/Widgets/AbstractButton.h>

class Header : public QWidget
{
    public:
        Header();
        AbstractButton *search;
        AbstractButton *expand;
};
