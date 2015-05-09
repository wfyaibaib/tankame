#ifndef GAMESCENE_H
#define GAMESCENE_H

#include <QGraphicsScene>
#include "./gamefactory/gamefactory.h"
// 游戏场景类
class GameScene : public QGraphicsScene
{
    Q_OBJECT

public:
    explicit GameScene(QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // GAMESCENE_H
