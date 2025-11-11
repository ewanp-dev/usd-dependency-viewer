#pragma once

#include <QWidget>
#include <QPushButton>
#include <Gui/Widgets/AbstractButton.h>

class Sidebar : public QWidget
{
    public:
        Sidebar();
        dvWidgets::AbstractButton *database;
        dvWidgets::AbstractButton *nodegraph;
        dvWidgets::AbstractButton *home;
        dvWidgets::AbstractButton *settings;
};
