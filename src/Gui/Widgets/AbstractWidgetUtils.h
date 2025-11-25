#pragma once

#include <QWidget>
#include <QPropertyAnimation>

namespace dvWidgets
{
    struct AbstractWidgetUtils
    {
        static void animateColor(
            QWidget* widget,
            const QColor& from,
            const QColor& to,
            int duration = 150
        );
    };
}
