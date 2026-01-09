#pragma once 

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

class Footer : public QWidget
{
    public:
        Footer(const std::string& dependencyPath = "", int numDependencies = 0, QWidget* parent = nullptr);

    private:
        QHBoxLayout* mainLayout_;

        QLabel*      startText_;
        QLabel*      dependencyPath_;
        QLabel*      dependencyDepth_;
        QLabel*      softwareVersion_;

};
