#pragma once

#include <QWidget>
#include <QPushButton>
#include <QPropertyAnimation>
#include <vector>

namespace dvWidgets
{
    class AbstractButton;

    struct AbstractWidgetUtils
    {
        static void animateColor(
            QWidget* widget,
            const QColor& from,
            const QColor& to,
            int duration = 150
        );

        static void setSelectedButtonItem(
            const std::vector<dvWidgets::AbstractButton*>& buttons, 
            QPushButton* activatedButton
        );

        static void setStyleProperty(
            QWidget* widget,
            const QString& className
        );
    };
}
