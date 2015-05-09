#ifndef BOUNDDEADLINEELEMENT_H
#define BOUNDDEADLINEELEMENT_H
#include "boundlineelement.h"

#include <QGraphicsObject>
class BoundDeadLineElement : public BoundLineElement


{
    Q_OBJECT

public:
    Q_INVOKABLE BoundDeadLineElement();
protected:

    int type() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // BOUNDDEADLINEELEMENT_H
