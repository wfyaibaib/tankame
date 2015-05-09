#include "./items/mapelements/bounddeadlineelement.h"
#include "./gamefactory/gamefactory.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QPen>
BoundDeadLineElement::BoundDeadLineElement()
{
    lineLength = 500;
    lineWidth = 8;
    QGraphicsObject::setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);
}

int BoundDeadLineElement::type() const
{
    return GameFactory::BOUND_DEAD_LINE;
}

QRectF BoundDeadLineElement::boundingRect() const
{
    return QRectF(0, 0, lineLength, lineWidth);
}

void BoundDeadLineElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QColor(Qt::red));
    painter->setBrush(QBrush(QColor(Qt::red)));
    painter->drawRect(boundingRect());
}

