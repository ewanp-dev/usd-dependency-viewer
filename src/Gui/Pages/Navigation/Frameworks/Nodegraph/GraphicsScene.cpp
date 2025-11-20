#include "GraphicsScene.h"
#include <QColor>

fdg::GraphicsScene::GraphicsScene(QObject *parent) : QGraphicsScene(parent) 
{
    setSceneRect(x_, y_, sceneWidth_, sceneHeight_);
    std::string background_color = "#171717";
    setBackgroundColor(background_color);
}

void fdg::GraphicsScene::setBackgroundColor(std::string& color) 
{
    QColor background_color(color.c_str());
    setBackgroundBrush(background_color);
}
