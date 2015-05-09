#include "bounddeadlineelement.h"
#include "./gamefactory/gamefactory.h"
#include <QGraphicsScene>
#include <QPainter>
#include <QDebug>
#include <QPen>
BoundDeadLineElement::BoundDeadLineElement()
{
    lineLength = 700;
    lineWidth = 8;
    QGraphicsObject::setFlags(QGraphicsItem::ItemIsSelectable |
                              QGraphicsItem::ItemIsMovable);
}

int BoundDeadLineElement::type() const
{
    return GameFactory::BOUND_DEAD_LINE;
}

void BoundDeadLineElement::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    painter->setPen(QColor(Qt::red));
    painter->setBrush(QBrush(QColor(Qt::red)));
    painter->drawRect(boundingRect());
}

