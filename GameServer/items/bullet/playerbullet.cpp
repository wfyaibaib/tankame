#include "playerbullet.h"
#include <QGraphicsScene>
#include "./items/tank/basetank.h"
#include "./gamefactory/gamefactory.h"
#include "./items/tank/playertank.h"
PlayerBullet::PlayerBullet()
{
}

PlayerBullet::~PlayerBullet()
{
     qDebug() << "PlayerBullet\tdctor:\tid =\t" << this->objectName().toInt();
}
// 玩家子弹
// 碰到不一个阵营坦克,(发现对方血量少于自身攻击,发出kill信号),令对方减血,自身请求销毁
void PlayerBullet::doCollision()
{
    auto collisionList = this->scene()->collidingItems(this);
    if (!collisionList.isEmpty())
    {
        // iterate all tank
        foreach (QGraphicsItem *item, collisionList)
        {
            BaseTank *tank = dynamic_cast<BaseTank*>(item);
            if (0 != tank && this->getTeam() != tank->getTeam())
            {
                if (tank->getLife() <= this->getDamage())
                { // qDebug() << "emit kill one!";
                   emit signal_bullet_kill_one();
                }
                tank->descreaseLife(getDamage());
            }
            GameFactory::createCommandRequestAndSend(GameFactory::DELETE,
                                                     this->type(),
                                                     this->objectName().toInt(),
                                                     GameFactory::property_list());
            return;
        }
    }
}

int PlayerBullet::type() const
{
    return GameFactory::PLAYER_BULLET;
}
