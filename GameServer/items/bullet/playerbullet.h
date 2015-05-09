#ifndef PLAYERBULLET_H
#define PLAYERBULLET_H
#include "basebullet.h"

class PlayerBullet :
                     public BaseBullet
{
    Q_OBJECT

public:
   Q_INVOKABLE explicit PlayerBullet();
    ~PlayerBullet();

    virtual void doCollision();
signals:
  void signal_bullet_kill_one();
public slots:
protected:
  int type() const;
    
};

#endif // PLAYERBULLET_H
