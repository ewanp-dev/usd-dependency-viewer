#include "ForceDirectedGraph.h"
#include "Edge.h"

#include <QPushButton>
#include <QTimer>
#include <QVBoxLayout>
#include <cmath>
#include <unordered_set>
#include <string>
#include <iostream>

fdg::ForceDirectedGraph::ForceDirectedGraph(QWidget* parent) 
    : view_(new fdg::GraphicsView()), scene_(new fdg::GraphicsScene(this))
{
    if (!parent)
        std::cout << "There is no parent" << '\n';

    setContentsMargins(0, 0, 0, 0);

    view_->setScene(scene_);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(view_);

    // NOTE:
    //
    // This is a temporary implementation of a properties
    // button on the nodegraph, will replace with a bespoke 
    // class later on

    propertiesButton_ = initPropertiesButton();
    setLayout(mainLayout);
    propertiesButton_->raise();
    propertiesButton_->move(12, 10);

}

void fdg::ForceDirectedGraph::initSimulation()
{
    if (nodeStore_.empty())
        return;

    timer_ = new QTimer(this);
    timer_->setTimerType(Qt::PreciseTimer);
    connect(timer_, &QTimer::timeout, this, &fdg::ForceDirectedGraph::tick);

    const int fps          = 60;
    constexpr int interval = static_cast<float>(1000) / 60;

    elapsed_.start();
    timer_->start(interval);

}

fdg::Node* fdg::ForceDirectedGraph::addNode(std::string name) 
{
    fdg::Node* node = new fdg::Node(name);

    scene_->addItem(node);

    connect(node, &fdg::Node::hoverEntered, this, &fdg::ForceDirectedGraph::onNodeHoverEnter);
    connect(node, &fdg::Node::hoverLeft, this, &fdg::ForceDirectedGraph::onNodeHoverLeave);

    nodeStore_.push_back(node);

    return node;
}

void fdg::ForceDirectedGraph::connectNodes(fdg::Node* startNode, fdg::Node* endNode)
{
    fdg::Edge* edge = new fdg::Edge(startNode, endNode);
    connectionStore_.push_back(edge);
    scene_->addItem(edge);
}

void fdg::ForceDirectedGraph::connectMultipleNodes(fdg::Node* startNode, const std::vector<fdg::Node*> &endNodes) 
{
    for (fdg::Node* node : endNodes) 
    {
        fdg::Edge* edge = new fdg::Edge(startNode, node);
        connectionStore_.push_back(edge);
        scene_->addItem(edge);
    } 
}

QPointF fdg::ForceDirectedGraph::computeRepulsion(fdg::Node* node) 
{
    const double kRepel = 400.0;
    QPointF velocityDelta(0.0, 0.0);

    for (fdg::Node* otherNode : nodeStore_) 
    {
        if (node == otherNode) 
        {
            continue;
        }

        QPointF repelDirection = node->pos() - otherNode->pos();
        const float length = sqrt(repelDirection.x()*repelDirection.x() + repelDirection.y()*repelDirection.y());

        repelDirection /= length;
        double magnitude = kRepel / length;

        velocityDelta += repelDirection * magnitude;
    }

    return velocityDelta;
}

QPointF fdg::ForceDirectedGraph::computeAttraction(fdg::Node* node)
{
    const double kSpring    = 0.05;
    const double restLength = 80.0; // Distance between nodes

    QPointF velocityDelta(0.0, 0.0);

    for (fdg::Edge* edge : node->getConnections()) 
    {
        fdg::Node* other = (edge->node == node) ? edge->input : edge->node;
        
        QPointF repelDirection = other->pos() - node->pos();
        const float length = sqrt(repelDirection.x()*repelDirection.x() + repelDirection.y()*repelDirection.y());
        repelDirection /= length;

        double magnitude = kSpring * (length - restLength);
        QPointF springForce = repelDirection * magnitude;

        velocityDelta += springForce;
    }

    return velocityDelta;
}

QPointF fdg::ForceDirectedGraph::computeCenterGravity(fdg::Node* node)
{
    QPointF center(scene_->sceneRect().center());
    QPointF delta = center - node->pos();
    const double gravity = 0.01;
    return delta * gravity;
}

void fdg::ForceDirectedGraph::updatePhysics(double dt) 
{
    for (fdg::Node* node : nodeStore_) 
    {
        QPointF repulsiveForce  = computeRepulsion(node);
        QPointF attractiveForce = computeAttraction(node);
        QPointF gravityForce    = computeCenterGravity(node);

        QPointF totalForce = repulsiveForce + attractiveForce + gravityForce;

        node->velocity += totalForce * dt;
        node->velocity *= 0.9;

        if (!node->isDragging()) 
        {
            node->setPos(node->pos() + node->velocity);
        }

        double speed = std::hypot(node->velocity.x(), node->velocity.y());
    }
}

void fdg::ForceDirectedGraph::tick() 
{
    const qint64 ns = elapsed_.nsecsElapsed();
    elapsed_.restart();

    double speedMultiplier = 5; // speed up or slow down the graph
    const double dt = ( ns * 1e-9 ) * speedMultiplier;

    updatePhysics(dt);

    scene_->update();
}

void fdg::ForceDirectedGraph::onNodeHoverEnter(fdg::Node* hoveredNode) 
{
    std::unordered_set<fdg::Node*> family = { hoveredNode };

    for (fdg::Edge* connection : hoveredNode->getOutputs()) 
    {
        connection->setFadeColor(QColor("#2c2f33"), QColor("#749e94"));
        family.insert(connection->node);
    }

    for (fdg::Node* node : nodeStore_) 
    {
        if (family.find(node) != family.end()) 
        {
            node->setFadeColor(QColor("#e9e9e9"), QColor("#749e94"));
        } else 
        {
            node->setFadeColor(QColor("#e9e9e9"), QColor("#404040"));
        }
    }
}

void fdg::ForceDirectedGraph::onNodeHoverLeave(fdg::Node* hoveredNode) 
{
    for (fdg::Edge* connection : hoveredNode->getOutputs()) 
    {
        connection->setFadeColor(QColor("#749e94"), QColor("#2c2f33"));
    }

    for (fdg::Node* node : nodeStore_) 
    {
        node->setFadeColor(node->brush().color(), QColor("#e9e9e9"));
    }
}

void fdg::ForceDirectedGraph::clearNodes()
{
    nodeStore_.clear();
    scene_->clear();
}

dvWidgets::AbstractButton* fdg::ForceDirectedGraph::initPropertiesButton()
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setParent(this);
    button->setIcon(QIcon(":icons/DarkMode/properties.png"));
    button->setFixedSize(48, 48);
    button->setIconSize(QSize(32, 32));
    button->setCheckable(false);

    nodegraphPropertiesWidget_ = nullptr;

    connect(button, &dvWidgets::AbstractButton::clicked, this, [this, button] () {

        if (nodegraphPropertiesWidget_ && nodegraphPropertiesWidget_->isVisible()) {
            return;
        }

        if (!nodegraphPropertiesWidget_) {
            nodegraphPropertiesWidget_ = new NodegraphPropertiesWidget(nullptr);
            nodegraphPropertiesWidget_->setAttribute(Qt::WA_DeleteOnClose);  // auto-delete when closed
            connect(nodegraphPropertiesWidget_, &QWidget::destroyed, this, [this]() {
                nodegraphPropertiesWidget_ = nullptr;
            });
        }

        nodegraphPropertiesWidget_->adjustSize();

        QPoint globalPos = button->mapToGlobal(QPoint(0, button->height()));

        nodegraphPropertiesWidget_->move(globalPos);
        nodegraphPropertiesWidget_->show();
        nodegraphPropertiesWidget_->raise();
    });

    return button;
}

void fdg::ForceDirectedGraph::setNodeAsSelected(const std::string& fileName)
{
    // for (fdg::Edge* edge : connectionStore_)
    // {
    //     edge->setFadeColor(QColor("#2c2f33"), QColor("#2c2f33"));
    // }

    for (fdg::Node* node : nodeStore_)
    {
        if (node->getNodePath() == fileName)
        {
            node->setFadeColor(node->brush().color(), QColor("#749e94"));
        } else
        {
            node->setFadeColor(node->brush().color(), QColor("#404040"));
        }
    }
}

std::vector<fdg::Node*> fdg::ForceDirectedGraph::nodeStore()
{
    return nodeStore_;
}
