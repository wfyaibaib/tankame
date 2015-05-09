#include "boundlineelement.h"
#include "./gamefactory/gamefactory.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QPen>
BoundLineElement::BoundLineElement()
{
    lineLength = 700;
    lineWidth = 8;
    QGraphicsObject::setFlags(QGraphicsItem::ItemIsSelectable |
                              QGraphicsItem::ItemIsMovable);
}

int BoundLineElement::type() const
{
    return GameFactory::BOUND_LINE;
}

QRectF BoundLineElement::boundingRect() const
{
    return QRectF(0, 0, lineLength, lineWidth);
}

void BoundLineElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QColor(Qt::black));
    painter->setBrush(QBrush(QColor(Qt::black)));
    painter->drawRect(boundingRect());
}


