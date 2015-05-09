#ifndef MYCLIENT_H
#define MYCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QString>
#include "./gamefactory/gamefactory.h"


// 服务器端 socket 的封装
class ClientRequestHolder : public QObject
{
    Q_OBJECT
public:
    explicit ClientRequestHolder(QObject *parent = 0);
    // 设置 socket 描述符
    void setSocket(int socketDescriptor);

signals:
    // 对象自身状态
    void signal_client_state(QString state);
    // 从玩家那得到聊天信息
    void signal_get_chat_message_from_client(QString message);

public slots:
    // socket 响应处理
    void connected();
    void disconnected();
    void readyRead();

    // 从pool里发送的命令,传递给每个客户端
    void postRequestToClient(GameFactory::GameCommandRequest  request);
    // 聊天信息
    void postChatMessageToClient(QString message);
    // 传递连杀命令
    void postMultiKillCommand(int MultiKill);

protected:
    QTcpSocket* socket;
};

#endif // MYCLIENT_H
