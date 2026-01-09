#include "Node.h"
#include "Edge.h"
#include <QGraphicsTextItem>
#include <QGraphicsSceneMouseEvent>
#include <QStyleOptionGraphicsItem>
#include <QPainter>
#include <QCursor>
#include <qnamespace.h>

fdg::Node::Node(std::string &nodeName, qreal x, qreal y, qreal w, qreal h, QGraphicsItem* parent) 
    : QGraphicsEllipseItem(parent), nodeName_(nodeName),
    x_(x), y_(y), nodeColor_("#bec4cf"),
    hoverColor_("#c9bf99"), charLimit_(12), label_(new QGraphicsTextItem(nodeName_.c_str(), this))
{
    setRect(-w, -h, 2 * w, 2 * h);
    setFlag(GraphicsItemFlag::ItemIsMovable);
    setFlag(GraphicsItemFlag::ItemIsSelectable);
    setFlag(GraphicsItemFlag::ItemSendsGeometryChanges);
    setAcceptHoverEvents(true);
    setPen(Qt::NoPen);
    setPos(x_, y_);
    setColor(nodeColor_);

    label_->setAcceptHoverEvents(false);
    label_->setDefaultTextColor(QColor(nodeColor_.c_str()));

    updateLabelPosition_(4);
}

void fdg::Node::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) 
{
    QStyleOptionGraphicsItem opt(*option);
    opt.state &= ~QStyle::State_Selected;
    QGraphicsEllipseItem::paint(painter, &opt, widget);
}

void fdg::Node::hoverEnterEvent(QGraphicsSceneHoverEvent *event) 
{
    hoverEntered(this);
    setColor(hoverColor_);
    setCursor(Qt::CursorShape::OpenHandCursor);
    updateLabelPosition_(6);
    update();
    QGraphicsEllipseItem::hoverEnterEvent(event);
}

void fdg::Node::hoverLeaveEvent(QGraphicsSceneHoverEvent *event) 
{
    hoverLeft(this);
    setDefaultColor();
    unsetCursor();
    updateLabelPosition_(4);
    update();
    QGraphicsEllipseItem::hoverLeaveEvent(event);
}

void fdg::Node::mousePressEvent(QGraphicsSceneMouseEvent *event) 
{
    
    if (event->button() != Qt::MouseButton::LeftButton) 
    {
        QGraphicsEllipseItem::mousePressEvent(event);
    } else 
    {
        isDragging_ = true;
    }
}

void fdg::Node::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) 
{
    setSelected(false);
    isDragging_ = false;
    QGraphicsEllipseItem::mouseReleaseEvent(event);
} 

void fdg::Node::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        Q_EMIT nodeDoubleClicked(getNodePath());
    }

    QGraphicsEllipseItem::mouseDoubleClickEvent(event);
}

QVariant fdg::Node::itemChange(GraphicsItemChange change, const QVariant &value) 
{
    if (change == GraphicsItemChange::ItemPositionHasChanged) 
    {
        setSelected(false);

        for (Edge* conn : connections_) 
        {
            conn->updatePosition();
        }
    }
    return QGraphicsEllipseItem::itemChange(change, value);
}

void fdg::Node::updateLabelPosition_(int y_pos) 
{
    QRectF nodeRect = rect();
    QRectF labelRect = label_->boundingRect();

    auto x = nodeRect.center().x() - (labelRect.width() / 2);
    auto y = nodeRect.bottom() + y_pos;
    label_->setPos(x, y);
}

void fdg::Node::setName(std::string& name) 
{
    nodeName_ = name;

    if (nodeName_.length() > this->charLimit_) 
    {
        nodeName_ = nodeName_.substr(0, 12);
    }

    label_->setPlainText(nodeName_.c_str());
    updateLabelPosition_(4);
}

std::string fdg::Node::getName() 
{
    return nodeName_;
}

void fdg::Node::addInput(Edge* input) 
{
    inputs_.push_back(input);
}

void fdg::Node::addOutput(Edge* output) 
{
    outputs_.push_back(output);
}

void fdg::Node::addConnection(Edge* connection) 
{
    connections_.push_back(connection);
}

std::vector<fdg::Edge*> fdg::Node::getInputs() 
{
    return inputs_;
}

std::vector<fdg::Edge*> fdg::Node::getOutputs() 
{
    return outputs_;
}

std::vector<fdg::Edge*> fdg::Node::getConnections() 
{
    return connections_;
}

void fdg::Node::setNodeRadius(float radius) 
{
    radius = (radius < 0.001) ? 0.001 : (radius > 150) ? 150 : radius;
    setRect(-radius / 2, -radius / 2, radius, radius);
}

QPointF fdg::Node::getCenterPosition() 
{
    return scenePos();
} 

void fdg::Node::setColor(const std::string &color) 
{
    QColor qcolor(color.c_str());
    setBrush(QBrush(qcolor));
    update();
}

void fdg::Node::setFadeColor(const QColor &start, const QColor &end, int duration) 
{
    // NOTE:
    //
    // Added the animation is a member, deleting it before 
    // starting another fadeColor as this was causing the 
    // enter and leave animations to overlap 

    if ( animation_ )
    {
        animation_->stop();
        animation_->deleteLater();
    }

    animation_ = new QVariantAnimation(this);
    animation_->setDuration(duration);
    animation_->setStartValue(start);
    animation_->setEndValue(end);

    connect(animation_, &QVariantAnimation::valueChanged, this, [this](const QVariant &value) 
    {
        QColor c = value.value<QColor>();
        setBrush(QBrush(c));
        if (label_) 
        {
            label_->setDefaultTextColor(c);
        }
        update();
    });

    connect(animation_, &QVariantAnimation::finished, this, [this]() 
    {
        animation_->deleteLater();
        animation_ = nullptr;
    });

    animation_->start();
}

void fdg::Node::setDefaultColor() 
{
    QColor qcolor(nodeColor_.c_str());
    setBrush(QBrush(qcolor));
}

bool fdg::Node::isDragging() const 
{
    return isDragging_;
}

void fdg::Node::setNodePath(const std::string& filePath)
{
    nodePath_ = filePath;
}

const std::string& fdg::Node::getNodePath()
{
    return nodePath_;
}
