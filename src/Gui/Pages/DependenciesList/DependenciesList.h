#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class DependenciesListPage : public QWidget
{
    public:
        DependenciesListPage(std::vector<std::string> dependencies, QWidget* parent = nullptr);

        void setTable(std::vector<std::string> items);

    private:
        QVBoxLayout* mainLayout_;
        QLabel* pageLabel_;
};
