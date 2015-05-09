#include "playerbullet.h"
#include <QGraphicsScene>
#include "./items/tank/basetank.h"
PlayerBullet::PlayerBullet()
{
}

void PlayerBullet::doCollision()
{
    auto collisionList = this->scene()->collidingItems(this);
    if (!collisionList.isEmpty())
    {
        foreach (QGraphicsItem *item, collisionList)
        {
            BaseTank *tank = dynamic_cast<BaseTank*>(item);
            if (0 != tank && this->getTeam() != tank->getTeam())
            {
                if (tank->getLife() <= this->getDamage())

                {
                    emit signal_bullet_kill_one();
                }
                tank->descreaseLife(getDamage());
            }
            scene()->removeItem(this);
            return;
        }
    }
}
