#pragma once

#include <QWidget>
#include "../AbstractButton.h"

class Header : public QWidget
{
    public:
        Header();
    private:
        AbstractButton *expand;
        AbstractButton *search;
};
