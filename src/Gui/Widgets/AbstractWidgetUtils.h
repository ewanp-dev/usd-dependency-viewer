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
            const QString& borderRadius = "4",
            const QString& padding = "8",
            const QString& settings = "",
            int duration = 150
        );

        static void setSelectedButtonItem(
            const std::vector<dvWidgets::AbstractButton*>& buttons, 
            QPushButton* activatedButton,
            const QString& borderRadius = "4",
            const QString& padding = "8"
        );
    };
}
