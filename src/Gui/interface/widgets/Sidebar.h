#pragma once

#include <QWidget>
#include <QPushButton>
#include "../AbstractButton.h"

class Sidebar : public QWidget
{
    public:
        Sidebar();
        AbstractButton *database;
        AbstractButton *nodegraph;
        AbstractButton *home;
        AbstractButton *settings;
};
