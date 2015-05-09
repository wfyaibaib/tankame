#include "basebullet.h"
#include <QPainter>
#include <QGraphicsScene>
#include <QDebug>
#include "./items/tank/basetank.h"
#include "./gamefactory/gamefactory.h"

BaseBullet::BaseBullet() : QGraphicsObject()
{
    speed = 7;
    damage= 2;
    team = 1;

    this->setFlag(QGraphicsItem::ItemIsSelectable);
}

BaseBullet::~BaseBullet()
{
    qDebug() << "BaseBullet\tdctor:\tid =\t" << this->objectName().toInt();
}
/*******************************************************************************/
QRectF BaseBullet::boundingRect() const
{
    return QRectF(-5, 0, 10, 10);
}
void BaseBullet::advance(int phase)
{
    if (!phase)
    {
        doCollision();
    }
    if (phase)
    {
        GameFactory::createCommandRequestAndSend(
                                                 GameFactory::SET_PROPERTY,
                                                 this->type(),
                                                 this->objectName().toInt(),
                                                 GameFactory::property_list() <<
                                                 GameFactory::createPair("pos", QVariant(mapToScene(0, speed)))
                                                 );

    }
}

void BaseBullet::paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget)
{
    // draw
    painter->setBrush(QBrush(QColor(Qt::blue)));
    painter->setRenderHint(QPainter::Antialiasing);
    painter->drawEllipse(boundingRect());
    // draw damage
//    painter->setBrush(QBrush(QColor(Qt::red)));
//    painter->drawText(boundingRect(), QString::number(getDamage()));


}


/*******************************************************************************/
int BaseBullet::getSpeed() const { return this->speed; }
void BaseBullet::setSpeed(int speed) { this->speed = speed; }
int BaseBullet::getTeam() const { return this->team; }
int BaseBullet::getDamage() const { return damage; }
void BaseBullet::setDamage(int damage) { this->damage = damage; }
void BaseBullet::setTeam(int team) { this->team = team; }
/*******************************************************************************/
int BaseBullet::type() const { return GameFactory::BASE_BULLET; }
/*******************************************************************************/
// (碰到非队友坦克,(发现对方血量少于自身攻击, 播放音乐), 请求对方减少伤害),子弹消失
void BaseBullet::doCollision()
{
    // 子弹碰撞,子弹必消失
    // 碰撞 到 坦克 若坦克非队友,子弹具有攻击性

    auto collisionList = this->scene()->collidingItems(this);
    if (!collisionList.isEmpty())
    {
        foreach (QGraphicsItem *item, collisionList)
        {
            if (GameFactory::oneItemHaveFlags(item, GameFactory::BRICK_ELEMENT))
            {

            }
            BaseTank *tank = dynamic_cast<BaseTank*>(item);
            if (0 != tank && this->getTeam() != tank->getTeam())
            {
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


