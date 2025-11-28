#pragma once 

// This widget will act as a replacement for the table widget item
// instead opting for a more visually pleasing way of presenting the 
// asset data

#include "ItemThumbnail.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <Gui/Widgets/AbstractButton.h>
#include <Core/DependencyNode.h>
#include <Core/NodePath.h>

class ItemWidget : public QWidget
{
    public:
        ItemWidget(
            std::shared_ptr<DependencyNode> activeNode,            
            QWidget* parent = nullptr
        );

    private:
        void initUI();
        void initInformationLayout();
        dvWidgets::AbstractButton* initButton();

        QHBoxLayout* mainLayout_;
        QVBoxLayout* labelLayout_;
        QVBoxLayout* favouriteLayout_;

        ItemThumbnail*  thumbnailWidget_;
        QLabel*         fileNameLabel_;
        QLabel*         filePathLabel_;
        QLabel*         childrenLabel_;
        QLabel*         dateModifiedLabel_;

        dvWidgets::AbstractButton* favouriteButton_;
        
        NodePath nodePath_;
        std::shared_ptr<DependencyNode> activeNode_;
};
