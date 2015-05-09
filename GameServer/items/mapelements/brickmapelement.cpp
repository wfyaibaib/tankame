#include "brickmapelement.h"
#include <QPainter>
#include "./gamefactory/gamefactory.h"
BrickMapElement::BrickMapElement()
{
    QGraphicsObject::setFlags(QGraphicsItem::ItemIsSelectable |
                              QGraphicsItem::ItemIsMovable);
    qDebug() << "brick ctor";

}

int BrickMapElement::type() const
{
    return GameFactory::BRICK_ELEMENT;
}

QRectF BrickMapElement::boundingRect() const
{
    return QRectF(20, 20, 20, 20);
}

void BrickMapElement::paint(QPainter *painter,
                            const QStyleOptionGraphicsItem *option,
                            QWidget *widget)
{
    static QPixmap pixmap = QPixmap(":/res/grass.jpg");
    painter->drawPixmap(boundingRect(), pixmap, pixmap.rect());
}


void BrickMapElement::advance(int phase)
{
    if (!phase)
    {
        doCollision();
    }
    else
    {
        GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                 this->type(),
                                                 this->objectName().toInt(),
                                                 GameFactory::property_list()
                                                 <<
                                                 GameFactory::createPair("pos", mapToScene(0, 0)));
    }
}

void BrickMapElement::doCollision()
{
    auto listItems= this->scene()->collidingItems(this);
    if (!listItems.isEmpty())
    {
        foreach (QGraphicsItem* item, listItems) {
            if (GameFactory::oneItemHaveFlags(item, GameFactory::BASE_BULLET)){
                qDebug() << "brick delete-------------------------------------------";
                GameFactory::createCommandRequestAndSend(GameFactory::DELETE,
                                                         this->type(),
                                                         this->objectName().toInt(),
                                                         GameFactory::property_list());
            }
        }

    }
}
