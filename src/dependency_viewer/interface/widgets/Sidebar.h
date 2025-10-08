#pragma once

#include <QWidget>
#include "../AbstractButton.h"

class Sidebar : public QWidget
{
    public:
        Sidebar();
    private:
        AbstractButton *database;
        AbstractButton *nodegraph;
        AbstractButton *home;
        AbstractButton *settings;
};
