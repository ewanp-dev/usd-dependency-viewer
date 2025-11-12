#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>

class AssetViewPage : public QWidget
{
    public:
        AssetViewPage(QWidget* parent = nullptr);

    private:
        QVBoxLayout* mainLayout_;
        QLabel* pageLabel_;
};
