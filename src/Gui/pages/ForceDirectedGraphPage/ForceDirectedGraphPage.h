#pragma once

#include <QWidget>
#include <QVBoxLayout>

#include <ForceDirectedGraph.h>

class ForceDirectedGraphPage : public QWidget
{
    public:
        ForceDirectedGraphPage(QWidget* parent = nullptr);
    private:
        ForceDirectedGraph* graph_;
        QVBoxLayout* mainLayout_;
};
