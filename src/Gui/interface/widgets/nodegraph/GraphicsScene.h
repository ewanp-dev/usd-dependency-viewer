#pragma once

#include <QGraphicsScene>
#include <QObject>

namespace fdg
{

class GraphicsScene : public QGraphicsScene 
{
public:
    GraphicsScene(QObject *parent = nullptr);
    void setBackgroundColor(std::string& color);

private:
    int sceneWidth_ = 64000;
    int sceneHeight_ = 64000;
    int x_ = -sceneWidth_ / 2;
    int y_ = -sceneHeight_ / 2;
};

}
