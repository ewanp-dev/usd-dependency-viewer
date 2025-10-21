#include "ForceDirectedGraphPage.h"
#include <QTimer>

ForceDirectedGraphPage::ForceDirectedGraphPage(QWidget* parent)
    : QWidget(parent), graph_(new ForceDirectedGraph(this))
{
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->addWidget(graph_);

    Node* nodeA = graph_->addNode("Hello World");
    Node* nodeB = graph_->addNode("Something");
    Node* nodeC = graph_->addNode("Foo");
    Node* nodeD = graph_->addNode("Bar");

    graph_->connectNodes(nodeA, nodeB);
    graph_->connectNodes(nodeC, nodeD);
    graph_->connectNodes(nodeB, nodeD);

    nodeB->setPos(-100.0, -50.0);
    nodeC->setPos(-320.0, 50.0);
    nodeD->setPos(100.0, 50.0);

    QTimer::singleShot(0, graph_, &ForceDirectedGraph::initSimulation);
}
