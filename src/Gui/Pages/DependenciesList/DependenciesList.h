#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DependenciesListPage : public QWidget
{
    public:
        DependenciesListPage(QWidget* parent = nullptr);

    private:
        QVBoxLayout* mainLayout_;
        QLabel* pageLabel_;
};
