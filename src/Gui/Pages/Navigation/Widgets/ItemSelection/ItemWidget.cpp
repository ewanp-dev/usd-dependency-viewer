#include "ItemWidget.h"

#include <Gui/Widgets/AbstractWidgetUtils.h>

#include <iostream>

ItemWidget::ItemWidget(std::shared_ptr<DependencyNode> activeNode, QWidget* parent)
    : activeNode_(activeNode)
{
    setMouseTracking(true);
    setFixedHeight(148);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    setChecked(false);

    initUI();
}

bool ItemWidget::checkState()
{
    return checkState_;
}

void ItemWidget::setChecked(bool condition)
{
    checkState_ = condition;
}

std::string ItemWidget::getFilePath()
{
    return filePath_.toStdString();
}

QWidget* ItemWidget::getContainer()
{
    return container;
}

bool ItemWidget::eventFilter(QObject* obj, QEvent* event)
{
    if (obj == favouriteButton_)
    {
        if (event->type() == QEvent::Enter)
        {
            favouriteButton_->setIcon(QIcon(":/icons/DarkMode/star_filled.png"));
        }
        else if (event->type() == QEvent::Leave)
        {
            if (!favouriteButton_->isChecked())
            {

                favouriteButton_->setIcon(QIcon(":/icons/DarkMode/star_outline.png"));
            }
        }
    }
    return QObject::eventFilter(obj, event);
}

void ItemWidget::initUI()
{

    container = new QWidget(this);
    auto* layout = new QVBoxLayout(this);
    mainLayout_ = new QHBoxLayout(container);

    thumbnailWidget_ = new ItemThumbnail();

    mainLayout_->addWidget(thumbnailWidget_);
    mainLayout_->addSpacing(8);

    initInformationLayout();

    mainLayout_->addLayout(labelLayout_);

favouriteLayout_ = new QVBoxLayout();
    favouriteButton_ = initButton();
    favouriteLayout_->addWidget(favouriteButton_);
    favouriteLayout_->addStretch();
    favouriteButton_->setCheckable(true);

    if (activeNode_->isFavourite())
    {
        favouriteButton_->setChecked(true);
    } else
    {
        favouriteButton_->setChecked(false);
    }

    favouriteButton_->installEventFilter(this);
    favouriteButton_->setToolTip("Favourite Item");

    mainLayout_->addLayout(favouriteLayout_);

    layout->addWidget(container);
    container->setCursor(Qt::PointingHandCursor);
    container->setStyleSheet(
        "border: none;"
        "background-color: #262626;"
        "padding: 0px 0px;"
        "border-radius: 8px;"
    );
    container->setAttribute(Qt::WidgetAttribute::WA_StyledBackground, true);
    container->setContentsMargins(8, 8, 8, 8);
}

void ItemWidget::initInformationLayout()
{
    labelLayout_ = new QVBoxLayout();

    fileName_ = QString(activeNode_->getFileName().c_str());
    filePath_ = QString(activeNode_->getFilePath().c_str());
    numChildren_ = QString("Children: " + QString::number(activeNode_->getNumChildren()));
    dateModified_ = QString("Date Modified: " + QString(activeNode_->getDateModifiedTime().c_str()));

    fileNameLabel_ = new QLabel(fileName_); 
    fileNameLabel_->setStyleSheet("color: #FEEED7;");
    QFont f = fileNameLabel_->font();
    f.setPointSize(12);
    f.setBold(true);
    fileNameLabel_->setFont(f);

    QFontMetrics fm(fileNameLabel_->font());

    // f.setPointSize(8);
    filePathLabel_ = new QLabel(filePath_);
    QFont smallerFont = filePathLabel_->font();
    smallerFont.setPointSize(8);
    filePathLabel_->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    filePathLabel_->setWordWrap(false);
    filePathLabel_->setMinimumWidth(1);
    filePathLabel_->setFont(smallerFont);
    filePathLabel_->setStyleSheet("color: #C7C5C5;");

    childrenLabel_ = new QLabel(numChildren_);
    childrenLabel_->setFont(smallerFont);

    dateModifiedLabel_ = new QLabel(dateModified_);
    dateModifiedLabel_->setFont(smallerFont);

    labelLayout_->addWidget(fileNameLabel_);
    labelLayout_->addWidget(filePathLabel_);
    labelLayout_->addWidget(childrenLabel_);
    labelLayout_->addSpacing(1);
    labelLayout_->addWidget(dateModifiedLabel_);
}

dvWidgets::AbstractButton* ItemWidget::initButton()
{
    dvWidgets::AbstractButton* button = new dvWidgets::AbstractButton();

    button->setFixedSize(28, 28);
    button->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    if (activeNode_->isFavourite())
    {
        button->setIcon(QIcon(":/icons/DarkMode/star_filled.png"));
    } else
    {
        button->setIcon(QIcon(":/icons/DarkMode/star_outline.png"));
    }

    button->setIconSize(QSize(24, 24));
    button->enableHoverEvent(false);

    connect(button, &dvWidgets::AbstractButton::clicked, this, [this, button] () {
        if (!button->isChecked())
        {
            button->setChecked(false);
            activeNode_->setFavourite(false);
        } else
        {
            button->setChecked(true);
            activeNode_->setFavourite(true);
        }
    });
    return button;
}

std::shared_ptr<DependencyNode> ItemWidget::asNode()
{
    return std::make_shared<DependencyNode>(filePath_.toStdString()); 
}

void ItemWidget::enterEvent(QEnterEvent* event)
{
    if (!checkState())
        dvWidgets::AbstractWidgetUtils::animateColor(container, startColor_, endColor_, "8", "0"); 
}

void ItemWidget::leaveEvent(QEvent* event)
{
    if (!checkState())
        dvWidgets::AbstractWidgetUtils::animateColor(container, endColor_, startColor_, "8", "0");
}

void ItemWidget::resizeEvent(QResizeEvent* event)
{
    QWidget::resizeEvent(event);

    QFontMetrics fm(filePathLabel_->font());
    int availableWidth = filePathLabel_->parentWidget()->contentsRect().width();
    filePathLabel_->setText(fm.elidedText(filePath_, Qt::ElideRight, availableWidth));
}

void ItemWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (activeNode_->getNumChildren() > 0) 
        Q_EMIT itemDoubleClicked(filePath_.toStdString());

    QWidget::mouseDoubleClickEvent(event);
}

void ItemWidget::mousePressEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (!checkState())
        {
            setChecked(true);
            container->setStyleSheet(
                "border: none;"
                "background-color: #749E94;"
                "padding: 0px 0px;"
                "border-radius: 8px;"
            );
            Q_EMIT itemActivated(filePath_.toStdString());
        } else
        {
            setChecked(false);
            container->setStyleSheet(
                "border: none;"
                "background-color: #262626;"
                "padding: 0px 0px;"
                "border-radius: 8px;"
            );
        }
    } else
    {
        QWidget::mousePressEvent(event); 
    }
}
