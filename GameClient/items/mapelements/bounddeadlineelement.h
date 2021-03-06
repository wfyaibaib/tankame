#ifndef BOUNDDEADLINEELEMENT_H
#define BOUNDDEADLINEELEMENT_H
#include "./items/mapelements/basesolidmapelement.h"

#include <QGraphicsObject>
class BoundDeadLineElement : public QGraphicsObject,
                             public BaseSolidMapElement

{
    Q_OBJECT

    Q_PROPERTY(int lineLength READ getLineLength WRITE setLineLength)
    Q_PROPERTY(int lineWidth READ getLineWidth WRITE setLineWidth)

public:
    Q_INVOKABLE BoundDeadLineElement();
protected:


    int lineLength;
    int lineWidth;
    int getLineLength() const { return lineLength; }
    int getLineWidth() const { return lineWidth; }
    void setLineLength(int lineLength) { this->lineLength = lineLength; }
    void setLineWidth(int lineWidth) { this->lineWidth = lineWidth; }

    int type() const;
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

};

#endif // BOUNDDEADLINEELEMENT_H
