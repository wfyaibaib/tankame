#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H

#include <QObject>
#include <QtDebug>
#include <QTcpServer>
#include "./gamefactory/gamefactory.h"
// 游戏服务器逻辑,处理客户端每个连接
class QThreadPool;

class GameTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit GameTcpServer(QObject *parent = 0);

    void startServer(int port);
    void askOneClientRequestHolderToPostMultiKillEffectToPlayerBySocketDescriptor(int descriptor, int multiKill);

signals:
    void signal_state(QString state);
    void signal_socketGetCommandRequest(GameFactory::GameCommandRequest request);

    void signal_serverPostRequestToAllClient(GameFactory::GameCommandRequest request);
    void signal_serverPostChatMessageToAllClient(QString message);
public slots:
    void serverPostChatMessageToAllClient(QString message);
protected:
    void incomingConnection(qintptr handle);

};

#endif // MYTCPSERVER_H
