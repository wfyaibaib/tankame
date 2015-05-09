#include "./clientgraphicsview/clientgraphicsview.h"
#include <QDebug>
#include <QKeyEvent>
ClientGraphicsView::ClientGraphicsView(QObject *parent)

{

}
// 玩家按键信息传递给服务器
void ClientGraphicsView::keyPressEvent(QKeyEvent *event)
{
    qDebug() << "ClientGraphicsView get KeyEvent!";
   emit signal_getKeyEventFromPlayer( event);
}

void ClientGraphicsView::keyReleaseEvent(QKeyEvent *event)
{
   qDebug() << "ClientGraphicsView get KeyEvent!";
   emit  signal_getKeyEventFromPlayer(event);
}
