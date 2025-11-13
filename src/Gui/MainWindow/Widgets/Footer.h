#pragma once 

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class Footer : public QWidget
{
    public:
        Footer(const std::string& dependencyPath = "", QWidget* parent = nullptr);

    private:
        QLabel* dependencyPath_;
        QLabel* dependencyDepth_;
        QLabel* softwareVersion_;

        QVBoxLayout* mainLayout_;
};
