#pragma once 

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class Footer : public QWidget
{
    public:
        Footer(const std::string& dependencyPath = "", QWidget* parent = nullptr);

    private:
        QLabel* startText_;
        QLabel* dependencyPath_;
        QLabel* dependencyDepth_;
        QLabel* softwareVersion_;

        QHBoxLayout* mainLayout_;
};
