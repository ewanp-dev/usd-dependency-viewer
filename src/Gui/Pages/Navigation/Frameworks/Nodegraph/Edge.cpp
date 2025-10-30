#include "Edge.h"
#include "Node.h"
#include <QPen>
#include <QVariantAnimation>

fdg::Edge::Edge(Node* node, Node* input, QGraphicsItem* parent) 
    : node(node), input(input), defaultColor_("#2c2f33")
{
    node->addInput(this);
    node->addConnection(this);
    input->addOutput(this);
    input->addConnection(this);
    setPen(QPen(QColor(defaultColor_.c_str()), 2));
    setZValue(-1.0);
    updatePosition();
}

void fdg::Edge::updatePosition() 
{
    setLine(
        node->getCenterPosition().x(),
        node->getCenterPosition().y(),
        input->getCenterPosition().x(),
        input->getCenterPosition().y()
    );
}

void fdg::Edge::setLineColor(std::string color) 
{
    setPen(QPen(QColor(color.c_str()), 2));
}

void fdg::Edge::setDefaultColor() 
{
    setLineColor(defaultColor_);
}

void fdg::Edge::setFadeColor(const QColor &start, const QColor &end, int duration) 
{
    auto *anim = new QVariantAnimation();
    anim->setDuration(duration);
    anim->setStartValue(start);
    anim->setEndValue(end);

    connect(anim, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) {
        QColor c = value.value<QColor>();
        this->setPen(QPen(c, 2));
        this->update();
    });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}


