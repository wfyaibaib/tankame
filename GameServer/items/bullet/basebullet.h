#ifndef BASEBULLET_H
#define BASEBULLET_H

#include <QGraphicsEllipseItem>
#include <QGraphicsObject>
#include <QObject>

class BaseBullet : public QGraphicsObject
{

Q_OBJECT
    Q_PROPERTY(int speed READ getSpeed WRITE setSpeed)
    Q_PROPERTY(int team  READ getTeam WRITE setTeam)
    Q_PROPERTY(int damage  READ getDamage WRITE setDamage)
public:
    Q_INVOKABLE BaseBullet();
    ~BaseBullet();
/*******************************************************************************/
    int getTeam() const;
    void setTeam(int team);
    int getDamage() const;
    void setDamage(int damage);
    int getSpeed() const;
    void setSpeed(int speed);


/*******************************************************************************/
    int type() const;

    virtual void doCollision();

protected:

    void advance(int phase);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

private:
    int speed;
    int damage;
    int team;

};

#endif // BASEBULLET_H
