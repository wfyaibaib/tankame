#include "gamescene.h"

GameScene::GameScene(QObject *parent) :
    QGraphicsScene(parent)
{
    this->setSceneRect(0, 0, 600, 600);
}
