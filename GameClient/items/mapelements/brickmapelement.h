#ifndef BRICKMAPELEMENT_H
#define BRICKMAPELEMENT_H
#include "./items/mapelements/basedestructiblemapelement.h"
#include <QGraphicsObject>
// 砖 图元
class BrickMapElement : public BaseDestructibleMapElement
{
public:
    BrickMapElement();

     int type() const;

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void advance(int phase);


};

#endif // BRICKMAPELEMENT_H
