#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include "./items/bullet/basebullet.h"

class PlayerBullet :
                     public BaseBullet
{
    Q_OBJECT
public:
    Q_INVOKABLE explicit PlayerBullet();

    virtual void doCollision();
signals:
  void signal_bullet_kill_one();
public slots:
    
};

#endif // PLAYERBULLET_H
