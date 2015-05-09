#ifndef BASETANK_H
#define BASETANK_H

#include <QGraphicsObject>

// 坦克基类
class BaseTank :  public QGraphicsObject
{
Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed)
    Q_PROPERTY(int team  READ getTeam WRITE setTeam)
    Q_PROPERTY(int life  READ getLife WRITE setLife)
public:
    Q_INVOKABLE explicit BaseTank();
/*******************************************************************************/
    int getTeam() const;
    void setTeam(int team_);

    int getLife() const;
    void setLife(int life_);

    int getSpeed() const;
    void setSpeed(int speed_);
/*******************************************************************************/
    int type() const;
/*******************************************************************************/
    virtual   void descreaseLife(int damage);
    virtual   void doCollision();
    virtual   void fire();
/*******************************************************************************/

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);

    int speed;
    int team;
    int life;

private:

};

#endif // BASETANK_H
