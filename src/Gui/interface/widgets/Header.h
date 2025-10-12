#pragma once

#include <QWidget>
#include "../AbstractButton.h"

class Header : public QWidget
{
    public:
        Header();
        AbstractButton *search;
        AbstractButton *expand;
};
