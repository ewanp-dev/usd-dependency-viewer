#pragma once

#include <QMainWindow>
#include <QVBoxLayout>
#include "Home.h"
#include "widgets/Sidebar.h"
#include "widgets/Header.h"

class DependencyViewer : public QMainWindow 
{
    public:
        DependencyViewer(QWidget *parent = nullptr);
    private:
        Sidebar *sidebar_;
        Header *header_;
        HomePage *homePage_;
};
