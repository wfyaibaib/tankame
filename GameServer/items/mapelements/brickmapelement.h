#ifndef BRICKMAPELEMENT_H
#define BRICKMAPELEMENT_H
#include "basedestructiblemapelement.h"
#include <QGraphicsObject>
class BrickMapElement : public QGraphicsObject,
                        public BaseDestructibleMapElement
{
    Q_OBJECT
public:
    Q_INVOKABLE BrickMapElement();

     int type() const;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);

    void doCollision();


};

#endif // BRICKMAPELEMENT_H
