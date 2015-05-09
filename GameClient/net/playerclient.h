#ifndef PLAYERCLIENT_H
#define PLAYERCLIENT_H
#include <QObject>
#include <QTcpSocket>
// 封装 客户端 socket
class QKeyEvent;
class PlayerClient : public QObject
{
    Q_OBJECT
public:
    explicit PlayerClient(QObject *parent = 0);
    
signals:
    void signal_client_state(QString state);
    void signal_get_chat_message_from_server(QString message);
public slots:

    void closeConnect();
    void connectToServer(const QHostAddress &ip, qint16 port);
    // 玩家对坦克的键盘操作
    void writeKeyEventToServer(QKeyEvent* event);
    // 聊天信息
    void writeChatMessageToServer(QString message);

     void connected();
     void disconnected();
     void readyRead();

    void addOneBaseTank();
private:
    QTcpSocket *socket;

};

#endif // PLAYERCLIENT_H
