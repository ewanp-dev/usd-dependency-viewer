#pragma once

#include <QGraphicsLineItem>
#include <QObject>

namespace fdg {

class Node;

class Edge : public QObject, public QGraphicsLineItem
{
    Q_OBJECT
    public:
        Edge(fdg::Node* node, fdg::Node* input, QGraphicsItem* parent = nullptr);
        fdg::Node* node;
        fdg::Node* input;
        void updatePosition();
        void setLineColor(std::string color);
        void setDefaultColor();
        void setFadeColor(const QColor &start, const QColor &end, int duration = 150);
    private:
        std::string defaultColor_;
};

}
