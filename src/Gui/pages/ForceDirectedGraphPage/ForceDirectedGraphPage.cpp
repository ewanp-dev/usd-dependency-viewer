#include "ForceDirectedGraphPage.h"

ForceDirectedGraphPage::ForceDirectedGraphPage(QWidget* parent)
    : QWidget(parent), graph_(new ForceDirectedGraph(this))
{
    mainLayout_ = new QVBoxLayout(this);
    mainLayout_->addWidget(graph_);
}
