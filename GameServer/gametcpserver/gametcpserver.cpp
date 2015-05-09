#include "gametcpserver.h"
#include <QtGlobal>
#include <QString>
#include <string>
#include "./clientrequestholder/clientrequestholder.h"
#include "./itemspool/itemspool.h"
#include "./gamefactory/gamefactory.h"

GameTcpServer::GameTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    qDebug() << "MyTcpServer Ctor begin!";

    // 游戏对象池 广播请求信号处理,服务器转发信号给每个 ClientRequestHolder
    connect(GameFactory::getPool(),
            SIGNAL(signal_PostCommandToNetwork(GameFactory::GameCommandRequest)),
            this,
            SIGNAL(signal_serverPostRequestToAllClient(GameFactory::GameCommandRequest)));
    //
    GameFactory::setupServer(this);
    qDebug() << "MyTcpServer Ctor!";

    // 玩家命令送到工厂:

}
// 启动服务器
void GameTcpServer::startServer(int port = 4000)
{
    if (listen(QHostAddress::Any, port))
    {
        emit signal_state("server start");
        qDebug() << "server start!";

    }
    else
    {
        emit signal_state("server not start");
        qDebug() << "server not start!";
    }
}

void GameTcpServer::askOneClientRequestHolderToPostMultiKillEffectToPlayerBySocketDescriptor(int descriptor,
                                                                                             int multiKill)
{
    ClientRequestHolder *holder = this->findChild<ClientRequestHolder*>(QString::number(descriptor));
    if (holder)
    {
        holder->postMultiKillCommand(multiKill);
        qDebug() << "server ask one client post multi kill effect";
    }
}
// 新连接请求
void GameTcpServer::incomingConnection(qintptr handle)
{
    emit signal_state("new connection come! \nDescriptor:" +
                      QString::number(handle));

    ClientRequestHolder *client = new ClientRequestHolder(this);
    client->setObjectName(QString::number(handle));

    // 捕获 ClientRequestHolder 状态
    connect(client, SIGNAL(signal_client_state(QString)),
            this, SIGNAL(signal_state(QString)));
    // 广播对象池信号处理
    connect(this, SIGNAL(signal_serverPostRequestToAllClient(GameFactory::GameCommandRequest)),
            client, SLOT(postRequestToClient(GameFactory::GameCommandRequest)));
    connect(client, SIGNAL(signal_get_chat_message_from_client(QString)),
            this, SLOT(serverPostChatMessageToAllClient(QString)));

    client->setSocket(handle);

}


void GameTcpServer::serverPostChatMessageToAllClient(QString message)
{
    qDebug() << "serverPostChatMessageToAllClient: " << message;
    QList<ClientRequestHolder*> all_Holder = this->findChildren<ClientRequestHolder*>();
    foreach (ClientRequestHolder* holder, all_Holder) {
        holder->postChatMessageToClient(message);
        qDebug() << "server post one message!";
    }
}
