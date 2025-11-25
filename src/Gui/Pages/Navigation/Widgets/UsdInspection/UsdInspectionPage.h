#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class UsdInspectionPage : public QWidget
{
    public: 
        UsdInspectionPage(QWidget* parent = nullptr);

    private:
        QVBoxLayout*  mainLayout_;

        QLabel*       pageLabel_;
}; 
