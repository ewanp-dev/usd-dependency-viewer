#pragma once

#include <QWidget>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QKeyEvent>
#include <Gui/Widgets/AbstractButton.h>

class NodegraphPropertiesWidget : public QWidget
{
    Q_OBJECT

    public:
        NodegraphPropertiesWidget(QWidget* parent = nullptr);

        bool showAllDependencies();
        bool allowHoverEvents();
        bool dimUnselectedNodes();

    protected:
        void leaveEvent(QEvent* event) override;
        void keyPressEvent(QKeyEvent* event) override;

    private:
        dvWidgets::AbstractButton* initButton(int num);

        QVBoxLayout* mainLayout_;
        
        QLabel* header_;
        QLabel* showAllDependenciesLabel_;
        QLabel* allowHoverEventsLabel_;
        QLabel* dimUnselectedNodesLabel_;

        bool showDependencies_ = false;
        bool allowHoverEvents_ = false;
        bool dimUnselectedNodes_ = false;
        std::vector<bool> selectionEvents_;

        dvWidgets::AbstractButton* showAllDependenciesButton_;
        dvWidgets::AbstractButton* allowHoverEventsButton_;
        dvWidgets::AbstractButton* dimUnselectedNodesButton_;
};
