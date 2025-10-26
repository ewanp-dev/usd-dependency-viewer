#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QElapsedTimer>
#include <vector>
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "Node.h"

namespace fdg
{

class ForceDirectedGraph : public QWidget
{
    public:
        ForceDirectedGraph(QWidget* parent = nullptr);

        fdg::Node* addNode(std::string name);
        void connectNodes(fdg::Node* startNode, fdg::Node* endNode);
        void connectMultipleNodes(fdg::Node* startNode, const std::vector<fdg::Node*>& endNodes);
        void clearNodes();
        void initSimulation();

    protected:
        void onNodeHoverEnter(fdg::Node* hoveredNode);
        void onNodeHoverLeave(fdg::Node* hoveredNode);

    private:
        void tick();
        void updatePhysics(double dt);
        QPointF computeRepulsion(fdg::Node* node);
        QPointF computeAttraction(fdg::Node* node);
        QPointF computeCenterGravity(fdg::Node* node);

        QTimer* timer_;
        QElapsedTimer elapsed_;
        std::vector<fdg::Node*> nodeStore_;

        GraphicsScene* scene_;
        GraphicsView* view_;

};

}
