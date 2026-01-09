#include "AbstractWidgetUtils.h"
#include "AbstractButton.h"

void dvWidgets::AbstractWidgetUtils::animateColor(
    QWidget* widget, 
    const QColor& from, 
    const QColor& to, 
    const QString& borderRadius,
    const QString& padding,
    const QString& settings,
    int duration
)
{
    widget->setProperty("bgColor", from);

    auto anim = new QPropertyAnimation(widget, "bgColor", widget);
    anim->setStartValue(from);
    anim->setEndValue(to);
    anim->setDuration(duration);

    QObject::connect(anim, &QVariantAnimation::valueChanged,
        widget,
        [widget, borderRadius, padding, settings] (const QVariant& v)
        {
            const QColor c = v.value<QColor>();
            widget->setStyleSheet(
                QString(
                    "background-color: %1;"
                    "border: none;"
                    "border-radius: %2px;"
                    "padding: %3px %3px"
                    "%4"
                ).arg(c.name()).arg(borderRadius).arg(padding).arg(settings)
            );
        }
    );

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void dvWidgets::AbstractWidgetUtils::setSelectedButtonItem(
    const std::vector<dvWidgets::AbstractButton*>& buttons, 
    QPushButton* activatedButton,
    const QString& borderRadius,
    const QString& padding
)
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
                QString(
                "background-color: #799E94;"
                "border: none;"
                "padding: %1px %1px;"
                "border-radius: %2px;"
                ).arg(padding).arg(borderRadius)
            );
        } else
        {
            button->setChecked(false);
            button->setStyleSheet(
                QString(
                "background-color: #262626;"
                "border: none;"
                "padding: %1px %1px;"
                "border-radius: %2px;"
                ).arg(padding).arg(borderRadius)
            );
        }
    }
}
