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

    up = left = down = right = firing = false;


    QObject::connect(multi_kill_timer, SIGNAL(timeout()), this, SLOT(shift_right()));
    multi_kill_timer->start();

}

void PlayerTank::doCollision()
{

}
void PlayerTank::fire()
{
    qDebug() << "fire() begin!";
    int bulletId = GameFactory::getNextUnusedIdFromPool();
    qDebug() << bulletId;

    auto Pos = mapToScene(0,
                          0 + boundingRect().height() + 3
                          );
    // 向pool关送命令
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::PLAYER_BULLET,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos", Pos )
                                             <<
                                             GameFactory::createPair("rotation", this->rotation())
                                             <<
                                             GameFactory::createPair("team", this->getTeam())

                                             );
    qDebug() << "create";

    QGraphicsObject* bullet = GameFactory::getGraphicsObjectFromPoolById(bulletId);
    QObject::connect(static_cast<PlayerBullet*>(bullet), SIGNAL(signal_bullet_kill_one()),
                    this, SLOT(kill_one()));
    qDebug() << "connect";

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

void PlayerTank::keyPressEvent(QKeyEvent *event)
{
    qDebug() << event->count();
    qDebug() << event->isAutoRepeat();
    qDebug() << event->text();

    static bool has_dir = true;
    has_dir  = false;
    switch (event->key())
    {
    case Qt::Key_A:
         left = true;
         has_dir = true;
            break;
    case Qt::Key_D:
         right = true;
         has_dir = true;
            break;
    case Qt::Key_W:
         up = true;
         has_dir = true;
            break;

    case Qt::Key_S:
        down = true;
        has_dir = true;
            break;
//
    case Qt::Key_Space:
        if (left || right || up || down) advance(2);
        fire();
            break;

    }
    int cnt = up + down + left + right;
    int degree = this->rotation();
    if (cnt == 1)
    {
        if (up)  degree = 180;
        if (left) degree = 90;
        if (down) degree = 0;
        if (right) degree = -90;
    }
    if (cnt == 2)
    {
        if (up && left) degree = 135;
        if (up && right) degree = -135;
        if (down && left) degree = 45;
        if (down && right) degree = -45;
    }

    // no new rotaion
    if (has_dir && degree == this->rotation())
    {
        advance(2);
    }
    else
    {// new rotation
    GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                             this->type(),
                                             this->objectName().toInt(),
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("rotation", degree));
    }


}

void PlayerTank::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key())
    {
    case Qt::Key_A:
         left = false;
            break;
    case Qt::Key_D:
         right = false;
            break;

    case Qt::Key_W:
         up = false;
            break;

    case Qt::Key_S:
        down = false;
            break;

    case Qt::Key_Space:
        firing = false;
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
    qDebug() << "play kill " << multi_cnt;

  //  GameFactory::playSoundEffect(static_cast<GameFactory::sound_enum>(multi_cnt));
    GameFactory::writeMultiKillCommandToSocketByPlayerTankId(this->objectName().toInt(),
                                                             multi_cnt);
}


void PlayerTank::advance(int phase)
{
    if (!phase)
    {
        doCollision();
    }
    if (phase == 1)
    {
        GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                 this->type(),
                                                 this->objectName().toInt(),
                                                 GameFactory::property_list()
                                                 <<
                                                 GameFactory::createPair("pos", QVariant(mapToScene(0, 0)))
                                                 );
    }
    if (2 == phase)
    {
        // new pos
        GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                 this->type(),
                                                 this->objectName().toInt(),
                                                 GameFactory::property_list()
                                                 <<
                                                 GameFactory::createPair("pos", QVariant(mapToScene(0, speed)))
                                                 );
    }

}

int PlayerTank::type() const
{
    return GameFactory::PLAYER_TANK;
}
