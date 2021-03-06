
#include <QPainter>
#include <QGraphicsScene>
#include <QTime>
#include <QDebug>

#include "./gamefactory/gamefactory.h"
#include "./items/bullet/basebullet.h"
#include "basetank.h"
/*******************************************************************************/
BaseTank::BaseTank()
{
    this->setFlag(QGraphicsItem::ItemIsMovable);
    this->setFlag(QGraphicsItem::ItemIsSelectable);   

    life = 12;    
    // rotation    
    setRotation(qrand() % 360);
    // speed
    this->speed = 5;
    // start position
    setPos(200, 200);
}

BaseTank::~BaseTank()
{
    qDebug() << "BaseTank\tdctor:\tid =\t" << this->objectName().toInt();
}
/*******************************************************************************/
int BaseTank::getTeam() const { return this->team; }
void BaseTank::setLife(int life_) { this->life = life_; }
int BaseTank::getSpeed() const { return speed; }
void BaseTank::setSpeed(int speed_) { this->speed = speed_; }
int BaseTank::type() const { return GameFactory::BASE_TANK; }
void BaseTank::setTeam(int team_) { this->team = team_; }
int BaseTank::getLife() const { return life; }
/*******************************************************************************/
QRectF BaseTank::boundingRect() const { return QRectF(-20, 0, 40, 60); }

void BaseTank::paint(QPainter *painter,
                     const QStyleOptionGraphicsItem *option,
                     QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);
// draw self
    if (this->type() == GameFactory::BASE_TANK)
    {
        painter->drawPixmap(this->boundingRect(),
                            QPixmap(":/res/tank.jpg"),
                            QPixmap(":/res/tank.jpg").rect());
    }
    else
    {
        painter->drawPixmap(this->boundingRect(),
                            QPixmap(":/res/tank.png"),
                            QPixmap(":/res/tank.png").rect());
    }

/*    QPen pen;
//    pen.setColor(Qt::red);
//    pen.setWidth(7);
//    painter->setPen(pen);
//    QFont font;
//    font.setBold(true);
//    font.setPointSize(20);
//    painter->setFont(font);

//// draw life
//    painter->drawText(QRectF(-20, 0, 40, 25),
//                      QString::number(this->getLife()));
//// draw team
//    painter->drawText(QRectF(-20, 30, 40, 25),
//
                     QString::number(this->getTeam()));
  */
}
/*******************************************************************************/
void BaseTank::advance(int phase)
{
    if (!phase)
    {
        doCollision();
    }
    if (phase)
    {   // new pos
        auto newPos = mapToParent(0, (speed));
        GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                 this->type(),
                                                 this->objectName().toInt(),
                                                 GameFactory::property_list()
                                                 << GameFactory::createPair("pos", QVariant(newPos)));
        // fire bullet;
        fire();
    }
}
/*******************************************************************************/
// 开火
void BaseTank::fire()
{
    if (qrand() % 40 == 0)
    {
        auto newPos = mapToScene(0,
                                 0 + boundingRect().height() + 3
                                 );
        int newID;
        GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                                 GameFactory::BASE_BULLET,
                                                 newID,
                                                 GameFactory::property_list()
                                                 << GameFactory::createPair("pos", QVariant(newPos))
                                                 << GameFactory::createPair("rotation", QVariant(this->rotation()))
                                                 << GameFactory::createPair("team", QVariant(this->getTeam()))
                                                 );
    }

}
/*******************************************************************************/
// 减少生命值,为0或负请求销毁
void BaseTank::descreaseLife(int damage)
{
    if ((life -= damage) <= 0)
    {
        qDebug() << "base tank life <= 0: " << this->objectName().toInt() << " " <<  this->getLife();
        GameFactory::createCommandRequestAndSend(GameFactory::DELETE,
                                                 this->type(),
                                                 this->objectName().toInt(),
                                                 GameFactory::property_list());


    }
    else
    {
        qDebug() << " base tank descrease life " << this->objectName().toInt();
    }
}
// 碰到死亡边界,播放音效,请求销毁
// 碰到坦克,不一个队,则调整
void BaseTank::doCollision()
{

    auto collisionList = this->scene()->collidingItems(this);
    // 碰撞有死亡线,die,返回
    if (!collisionList.isEmpty())
    {
        foreach (QGraphicsItem *item, collisionList)
        {
            if (item->type() == GameFactory::BOUND_DEAD_LINE)
            {
                GameFactory::playSoundEffect(GameFactory::DIE_SOUND);
                GameFactory::createCommandRequestAndSend(GameFactory::DELETE,
                                                         this->type(),
                                                         this->objectName().toInt(),
                                                         GameFactory::property_list());

                return;
            }
        }

       foreach (QGraphicsItem *item, collisionList)
       {
            // 撞不一个队的坦克,调整
           if (!GameFactory::twoItemsHaveSameFlags(this, item, GameFactory::BASE_TANK) ||
               !GameFactory::twoTanksHaveSameTeam(this, item))
           {

               auto newRotation = (this->rotation() + 150+ qrand() % 60 );// 原点旋转180

               GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                        this->type(),
                                                        this->objectName().toInt(),
                                                        GameFactory::property_list()
                                                        << GameFactory::createPair("rotation", QVariant(newRotation))


                                                        );
               // 后退高度
               int random_dis =  3 + qrand() % (int(boundingRect().height())/2);
               QPointF newPos = mapToScene(0,
                                           -this->boundingRect().height() + random_dis);
               GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                        this->type(),
                                                        this->objectName().toInt(),
                                                        GameFactory::property_list()
                                                        << GameFactory::createPair("pos", QVariant(newPos))

                                                        );
               return;
           }
       }


    }

}
/*******************************************************************************/
