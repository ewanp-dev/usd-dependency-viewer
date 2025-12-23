#include "AbstractWidgetUtils.h"
#include "AbstractButton.h"

#include <QStyle>

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
            setStyleProperty(button, "ClassHoveredAbstractButton");
        } else
        {
            button->setChecked(false);
            setStyleProperty(button, "ClassDefaultAbstractButton");
        }
    }
}

void dvWidgets::AbstractWidgetUtils::setStyleProperty(QWidget* widget, const QString& className)
{
    // There are a few times in the application where the style sheet needs to change
    // like on hover events, this avoids any boilerplate code for style sheets 

    widget->setProperty("class", className);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
}
