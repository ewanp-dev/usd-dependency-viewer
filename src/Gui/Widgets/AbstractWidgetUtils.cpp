#include "AbstractWidgetUtils.h"
#include "AbstractButton.h"

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

void dvWidgets::AbstractWidgetUtils::setSelectedButtonItem(const std::vector<dvWidgets::AbstractButton*>& buttons, QPushButton* activatedButton)
{
    // This is a hacky solution to having selected pages reflect on the buttons
    // we can probably implement this in the qss at some point or using a 
    // custom property
    
    for ( dvWidgets::AbstractButton* button : buttons )
    {
        if ( button == activatedButton )
        {
            button->setChecked(true);
            button->setStyleSheet(
                "background-color: #799E94;"
                "border: none;"
                "padding: 8px 8px;"
            );
        } else
        {
            button->setChecked(false);
            button->setStyleSheet(
                "background-color: #262626;"
                "border: none;"
                "padding: 8px 8px;"
            );
        }
    }
}
