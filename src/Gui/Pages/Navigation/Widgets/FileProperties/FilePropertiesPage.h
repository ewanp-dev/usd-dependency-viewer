#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class FilePropertiesPage : public QWidget
{
    public: 
        FilePropertiesPage(QWidget* parent = nullptr);

    private:
        QVBoxLayout*  mainLayout_;

        QLabel*       pageLabel_;
}; 
