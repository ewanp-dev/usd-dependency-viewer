#include "GraphicsView.h"
#include <QMouseEvent>
#include <QScrollBar>

fdg::GraphicsView::GraphicsView(QWidget *parent) : QGraphicsView(parent) 
{
    setRenderHints(
        QPainter::RenderHint::Antialiasing      |
        QPainter::RenderHint::TextAntialiasing  |
        QPainter::RenderHint::SmoothPixmapTransform
    );

    setDragMode(QGraphicsView::DragMode::NoDrag);
    setHorizontalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarPolicy::ScrollBarAlwaysOff);
}

void fdg::GraphicsView::mousePressEvent(QMouseEvent *event) 
{
    if (event->button() == Qt::MouseButton::MiddleButton) 
    {
        lastMousePos_ = event->pos();
        isPanning_ = true;
        event->accept();
    } else 
    {
        QGraphicsView::mousePressEvent(event);
    }
}

void fdg::GraphicsView::mouseMoveEvent(QMouseEvent *event) 
{
    if (isPanning_) 
    {
        QPoint delta = event->pos() - lastMousePos_;

        lastMousePos_ = event->pos();

        float horizontalBarPos = horizontalScrollBar()->value() - delta.x();
        horizontalScrollBar()->setValue(horizontalBarPos);

        float verticalBarPos = verticalScrollBar()->value() - delta.y();
        verticalScrollBar()->setValue(verticalBarPos);

        event->accept();
    } else 
    {
        QGraphicsView::mouseMoveEvent(event);
    }
}

void fdg::GraphicsView::mouseReleaseEvent(QMouseEvent *event) 
{
    if (event->button() == Qt::MouseButton::MiddleButton) 
    {
        lastMousePos_ = QPoint();
        isPanning_ = false;
        event->accept();
    } else 
    {
        QGraphicsView::mouseReleaseEvent(event);
    }
}

void fdg::GraphicsView::wheelEvent(QWheelEvent *event) 
{
    QPointF oldPos = mapToScene(event->position().toPoint());

    bool isZoomingOut = event->angleDelta().y() < 0;
    float factor      = isZoomingOut ? 1 / zoomFactor_ : zoomFactor_;\
    float newZoom     = zoomCurrent_ * factor;

    if (zoomMin_ <= newZoom && newZoom <= zoomMax_) 
    {
        zoomCurrent_ = newZoom;
        scale(factor, factor);

        QPointF newPos = mapToScene(event->position().toPoint());
        QPointF delta  = newPos - oldPos;

        translate(delta.x(), delta.y());
    }
}
