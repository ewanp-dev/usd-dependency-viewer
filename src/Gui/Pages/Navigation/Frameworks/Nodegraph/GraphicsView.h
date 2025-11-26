#pragma once

#include <QGraphicsView>

namespace fdg
{

class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = nullptr);

    void mousePressEvent(QMouseEvent *event)   override;
    void mouseMoveEvent(QMouseEvent *event)    override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event)        override;

private:
    QPoint lastMousePos_;

    bool   isPanning_   = false;
    float  zoomFactor_  = 1.15f;
    float  zoomMin_     = 0.1f;
    float  zoomMax_     = 10.0f;
    float  zoomCurrent_ = 1.0f;

};

}
