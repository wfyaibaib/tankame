#include "playertank.h"
#include <QKeyEvent>
#include <QGraphicsScene>
#include "basetank.h"
#include "./items/bullet/playerbullet.h"
PlayerTank::PlayerTank()
{
    this->setLife(100);
    this->setFlag(QGraphicsItem::ItemIsFocusable);
    this->speed = 20;

    multi_kill_timer = new QTimer(this);
    multi_kill_timer->setInterval(2000);
    multi_kill_count_flags = 0;

    QObject::connect(multi_kill_timer, SIGNAL(timeout()), this, SLOT(shift_right()));
    multi_kill_timer->start();

}

void PlayerTank::doCollision()
{

}
void PlayerTank::processKeyEvent(QKeyEvent *event)
{
    if (event->type() == QKeyEvent::KeyPress)
    {
        keyPressEvent(event);
    }
    if (event->type() == QKeyEvent::KeyRelease)
    {
        keyReleaseEvent(event);
    }
}

void PlayerTank::fire()
{
    // 向pool关送命令

    PlayerBullet *bullet = new PlayerBullet();
    bullet->setRotation(this->rotation());
    bullet->setPos(mapToScene(0,
                              0 + boundingRect().height()
                              )
                   );
    bullet->setTeam(getTeam());
    QObject::connect(bullet, SIGNAL(signal_bullet_kill_one()), this, SLOT(kill_one()));
    this->scene()->addItem(bullet);


}

void PlayerTank::keyPressEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A:
         setRotation(90);
         advance(2);
         break;
    case Qt::Key_D:
        setRotation(-90);
        advance(2);
        break;
    case Qt::Key_W:
         setRotation(180);
         advance(2);
         break;
    case Qt::Key_S:
        setRotation(0);
        advance(2);
        break;
    case Qt::Key_Space:
        fire();
        break;
    }
}

void PlayerTank::shift_right()
{
    multi_kill_count_flags >>= 1;
}

void PlayerTank::kill_one()
{
    shift_right();
    multi_kill_count_flags |= 0x8;
    multi_kill_count_flags &= 0xF;

    int multi_cnt = 1;
    multi_cnt += multi_kill_count_flags & 0x1;
    if (multi_kill_count_flags & 0x2) multi_cnt++;
    if (multi_kill_count_flags & 0x4) multi_cnt++;
    qDebug() << "kill " << multi_cnt;
    GameFactory::playSoundEffect(static_cast<GameFactory::sound_enum>(multi_cnt));
}


void PlayerTank::advance(int phase)
{
    if (!phase)
    {
        doCollision();
    }
    if (2 == phase)
    {
        // new pos
        setPos(mapToScene(0, speed));
    }

}


int PlayerTank::type() const
{
    return GameFactory::PLAYER_TANK;
}
