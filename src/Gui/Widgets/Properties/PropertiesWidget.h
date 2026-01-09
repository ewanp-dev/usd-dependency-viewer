#pragma once

#include <QWidget>
#include <QVBoxLayout>

class PropertiesWidget : public QWidget
{
    public:
        PropertiesWidget(QWidget* parent = nullptr);

    private:
        void initUI();

        QVBoxLayout* mainLayout_;
};
