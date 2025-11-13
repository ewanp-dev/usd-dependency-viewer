#pragma once 

#include <QWidget>
#include <QLineEdit>
#include <QHBoxLayout>
#include <Gui/Widgets/AbstractButton.h>

class TableHeader : public QWidget
{
    public:
        TableHeader(QWidget* parent = nullptr);

        QLineEdit* dependencyPathWidget();

    private:
        QLineEdit* dependencyPath_;

        dvWidgets::AbstractButton* propertiesButton_;
        dvWidgets::AbstractButton* homeButton_;
        dvWidgets::AbstractButton* upButton_;

        QHBoxLayout* mainLayout_;

        const int FIXED_BUTTON_SIZE_ = 20;
        const QSize FIXED_ICON_SIZE_ = QSize(18, 18);

        dvWidgets::AbstractButton* initButton(const std::string& iconPath);
};
