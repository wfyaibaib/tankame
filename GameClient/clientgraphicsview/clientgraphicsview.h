#ifndef CLIENTGRAPHICSVIEW_H
#define CLIENTGRAPHICSVIEW_H

#include <QGraphicsView>

class ClientGraphicsView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit ClientGraphicsView(QObject *parent = 0);
    
signals:
    void signal_getKeyEventFromPlayer( QKeyEvent *event);
public slots:
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);


    
};

#endif // CLIENTGRAPHICSVIEW_H
