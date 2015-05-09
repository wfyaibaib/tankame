#include "clientrequestholder.h"
#include <QString>
#include <QHostAddress>
#include <QDataStream>
#include "./gamefactory/gamefactory.h"
#include <QKeyEvent>
ClientRequestHolder::ClientRequestHolder(QObject *parent) :
    QObject(parent)
{
    // pool 里发来请求处理, 发送给客户端

    qDebug() << "ClientRequestHolder ctor!";
}

void ClientRequestHolder::setSocket(int socketDescriptor)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    socket->setSocketDescriptor(socketDescriptor);
    // new connect , add tank for player
    GameFactory::addPlayerTankBySocketDescriptor(socketDescriptor);

    qDebug() << "ClientRequestHolder socket set!";
}

void ClientRequestHolder::connected()
{
    qDebug() << "ClientRequestHolder connected!";
    emit signal_client_state( "Ip: " + socket->peerAddress().toString() +
                              " Port: " + QString::number(socket->peerPort()) +
                              " connect!");
}


void ClientRequestHolder::disconnected()
{
    emit signal_client_state( "Ip: " + socket->peerAddress().toString() +
                              " Port: " + QString::number(socket->peerPort()) +
                              " disconnect!");
    qDebug() << "ClientRequestHolder disconnected!";

    this->deleteLater();
}

void ClientRequestHolder::readyRead()
{
    qDebug() << "ClientRequestHolder::readyRead()";
// 从游戏客户端读取,聊天信息或键盘坦克操作命令
    static quint16 nextBlockSize = 0;
    QDataStream in(socket);
    while (1)
    {
        // read size
        if (nextBlockSize == 0)// need read new block size
        {
            if (socket->bytesAvailable() < sizeof (quint16)) break;
            else
            {
                in >> nextBlockSize;
             //   qDebug() << "read size = " << nextBlockSize;
            }
        }
        if (socket->bytesAvailable() < nextBlockSize)
        {
            break; // wait for coming byte..
        }
        // read
        int command;
        in >> command ;
        qDebug() << "read command: " << command;
        if (command == GameFactory::CHAT)
        {
            QString message;
            in >> message;
            // add ip address
            message = socket->peerAddress().toString() + "\t" + message;
            qDebug() << "ClientRequestHolder read message from client: " << message;
            emit signal_get_chat_message_from_client(message);
        }
        else if (command == GameFactory::KEY_EVENT)
        {// 玩家对坦克的操作
            int event_type;
            int key_value ;
            in >> event_type;
            in >> key_value;
            // 构造keyEvent
            QKeyEvent *event = new QKeyEvent(static_cast<QEvent::Type>(event_type),
                                             key_value,
                                             Qt::NoModifier);
            qDebug() << "event ctor! type:" << event->type()
                     << " text: " << event->text()
                     << " value: " << event->key();
            GameFactory::postKeyEventToPlayerTankBySocketDescriptor(socket->socketDescriptor(), event);

        }
        // reset next block size
        nextBlockSize = 0;
    }


}
// 发送请求给客户端
void ClientRequestHolder::postRequestToClient(GameFactory::GameCommandRequest request)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly );

    stream << quint16(0);

    stream << request.command ;
    stream << request.type;
    stream << request.id ;
    stream << request.propertyList;

    stream.device()->seek(0);
    stream << quint16(array.size() - sizeof(quint16));

    socket->write(array);

    socket->flush();
}

void ClientRequestHolder::postChatMessageToClient(QString message)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly );

    stream << quint16(0);

    stream << GameFactory::CHAT ;
    stream << message;

    stream.device()->seek(0);
    stream << quint16(array.size() - sizeof(quint16));

    socket->write(array);

    socket->flush();
    qDebug() << "ClientRequestHolder::postChatMessageToClient :" << message;
}

void ClientRequestHolder::postMultiKillCommand(int MultiKill)
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly );

    stream << quint16(0);

    stream << GameFactory::MULTI_KILL ;
    stream << MultiKill;

    stream.device()->seek(0);
    stream << quint16(array.size() - sizeof(quint16));

    socket->write(array);

    socket->flush();
    qDebug() << "ClientRequestHolder::postMultiKillCommand :" << MultiKill;

}



