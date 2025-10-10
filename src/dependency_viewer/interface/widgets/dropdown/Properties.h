#pragma once

#include <QWidget>
#include <QCheckBox>

class PropertiesDropdownWidget : public QWidget
{
    public:
        PropertiesDropdownWidget(QWidget *parent=nullptr);
    private:
        QCheckBox *checkName_;
        QCheckBox *checkPath_;
        QCheckBox *checkSize_;
        QCheckBox *checkExtension_;
        QCheckBox *checkModified_;
};
