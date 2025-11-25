#include "AbstractWidgetUtils.h"

#include <iostream>

void dvWidgets::AbstractWidgetUtils::animateColor(QWidget* widget, const QColor& from, const QColor& to, int duration)
{
    widget->setProperty("bgColor", from);

    auto anim = new QPropertyAnimation(widget, "bgColor", widget);
    anim->setStartValue(from);
    anim->setEndValue(to);
    anim->setDuration(duration);

    QObject::connect(anim, &QVariantAnimation::valueChanged,
        widget,
        [widget] (const QVariant& v)
        {
            const QColor c = v.value<QColor>();
            widget->setStyleSheet(
                QString(
                    "background-color: %1;"
                    "border: none;"
                    "padding: 8px 8px;"
                ).arg(c.name())
            );
        }
    );

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}
