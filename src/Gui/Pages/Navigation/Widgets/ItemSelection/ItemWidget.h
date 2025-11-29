#pragma once 

// This widget will act as a replacement for the table widget item
// instead opting for a more visually pleasing way of presenting the 
// asset data

#include "ItemThumbnail.h"

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMouseEvent>
#include <Gui/Widgets/AbstractButton.h>
#include <Core/DependencyNode.h>
#include <Core/NodePath.h>

class ItemWidget : public QWidget
{
    Q_OBJECT

    Q_SIGNALS:
        void itemDoubleClicked(const std::string& filePath);

    public:
        ItemWidget(
            std::shared_ptr<DependencyNode> activeNode,            
            QWidget* parent = nullptr
        );

    protected:
        void enterEvent(QEnterEvent* event) override;
        void leaveEvent(QEvent* event) override;
        void resizeEvent(QResizeEvent* event) override;
        void mouseDoubleClickEvent(QMouseEvent* event) override;
        bool eventFilter(QObject* obj, QEvent* event) override;

    private:
        void initUI();
        void initInformationLayout();
        dvWidgets::AbstractButton* initButton();
        std::shared_ptr<DependencyNode> asNode();

        QHBoxLayout* mainLayout_;
        QVBoxLayout* labelLayout_;
        QVBoxLayout* favouriteLayout_;

        QWidget* container;
        ItemThumbnail*  thumbnailWidget_;
        QLabel*         fileNameLabel_;
        QLabel*         filePathLabel_;
        QLabel*         childrenLabel_;
        QLabel*         dateModifiedLabel_;

        QString fileName_;
        QString filePath_;
        QString numChildren_;
        QString dateModified_;
        
        const QColor startColor_ = QColor("#262626");
        const QColor endColor_   = QColor("#749E94");

        dvWidgets::AbstractButton* favouriteButton_;
        
        NodePath nodePath_;
        std::shared_ptr<DependencyNode> activeNode_;
};
