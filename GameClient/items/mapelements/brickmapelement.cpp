#include "brickmapelement.h"
#include <QPainter>
#include "./gamefactory/gamefactory.h"
BrickMapElement::BrickMapElement()
{
}

int BrickMapElement::type() const
{
    return GameFactory::BRICK_ELEMENT;
}

QRectF BrickMapElement::boundingRect() const
{
    return QRectF(20, 20, 20, 20);
}

void BrickMapElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    static QPixmap pixmap = QPixmap(":/res/brick.png");
    painter->drawPixmap(boundingRect(), pixmap, pixmap.rect());
}


void BrickMapElement::advance(int phase)
{
}
