#include "ItemWidget.h"

ItemWidget::ItemWidget(std::shared_ptr<DependencyNode> activeNode, QWidget* parent)
    : activeNode_(activeNode)
{
    setFixedHeight(128);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    initUI();
}

void ItemWidget::initUI()
{

    mainLayout_ = new QHBoxLayout(this);

    thumbnailWidget_ = new ItemThumbnail();

    mainLayout_->addWidget(thumbnailWidget_);

    initInformationLayout();

    mainLayout_->addLayout(labelLayout_);

    favouriteLayout_ = new QVBoxLayout();
    favouriteButton_ = initButton();
    favouriteLayout_->addWidget(favouriteButton_);

    mainLayout_->addLayout(favouriteLayout_);
}

void ItemWidget::initInformationLayout()
{
    labelLayout_ = new QVBoxLayout();

    fileNameLabel_ = new QLabel(activeNode_->getFileName().c_str()); 
    filePathLabel_ = new QLabel(activeNode_->getFilePath().c_str());
    childrenLabel_ = new QLabel(QString::number(activeNode_->getNumChildren()));
    // dateModifiedLabel_ = new QLabel(activeNode_->getDateModifiedTime().c_str());

    labelLayout_->addWidget(fileNameLabel_);
    labelLayout_->addWidget(filePathLabel_);
    labelLayout_->addWidget(childrenLabel_);
    labelLayout_->addWidget(dateModifiedLabel_);
}

dvWidgets::AbstractButton* ItemWidget::initButton()
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setFixedSize(28, 28);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    button->setIcon(QIcon(":/icons/DarkMode/star_outline.png"));
    button->setIconSize(QSize(24, 24));

    return button;
}
