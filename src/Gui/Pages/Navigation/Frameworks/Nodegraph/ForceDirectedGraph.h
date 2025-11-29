#pragma once

#include <QWidget>
#include <QGraphicsScene>
#include <QElapsedTimer>
#include <vector>
#include "GraphicsView.h"
#include "GraphicsScene.h"
#include "Node.h"
#include <Gui/Widgets/AbstractButton.h>
#include <Gui/Pages/Navigation/Widgets/Nodegraph/NodegraphPropertiesWidget.h>

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
        void setNodeAsSelected(const std::string& fileName);
        std::vector<fdg::Node*> nodeStore();

    protected:
        void onNodeHoverEnter(fdg::Node* hoveredNode);
        void onNodeHoverLeave(fdg::Node* hoveredNode);

    private:
        QPointF computeRepulsion(fdg::Node* node);
        QPointF computeAttraction(fdg::Node* node);
        QPointF computeCenterGravity(fdg::Node* node);
        void updatePhysics(double dt);
        void tick();
        dvWidgets::AbstractButton* initPropertiesButton();

        QTimer*        timer_;
        QElapsedTimer  elapsed_;

        GraphicsScene* scene_;
        GraphicsView*  view_;
        dvWidgets::AbstractButton* propertiesButton_;
        NodegraphPropertiesWidget* nodegraphPropertiesWidget_;

        std::vector<fdg::Node*> nodeStore_;
        std::vector<fdg::Edge*> connectionStore_;
};

}
