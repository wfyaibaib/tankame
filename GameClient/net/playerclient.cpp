#include "playerclient.h"
#include "./gamefactory/gamefactory.h"
#include "QHostAddress"
#include <QHostInfo>
#include <QTime>
#include <QDate>
#include <QKeyEvent>
#include <QDebug>
PlayerClient::PlayerClient(QObject *parent)
{
    socket = new QTcpSocket(this);
}

void PlayerClient::closeConnect()
{
    socket->close();
}

void PlayerClient::connected()
{
    emit signal_client_state("connect to server!");
}

void PlayerClient::disconnected()
{
    emit signal_client_state("disconnect!");
}
// 从服务器收到一条命令,扔到客户端图元工厂,或是聊天信息,或连杀特效命令
void PlayerClient::readyRead()
{
/*******************************************************************************/
    static quint16 nextBlockSize = 0;
    QDataStream in(socket);
/*******************************************************************************/
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
/*******************************************************************************/
        // read
        int command;
        in >> command ;
        qDebug() << "PlayerClient::readyRead() command:" << command;
        if (command == GameFactory::CHAT)
        {
            QString message;
            in >> message;
             qDebug() << "PlayerClient::readyRead() chat message:" << message;
            emit signal_get_chat_message_from_server(message);
        }
/*******************************************************************************/

/*******************************************************************************/
        else if (command == GameFactory::MULTI_KILL)
        {
            int multiKill;
            in >> multiKill;
            GameFactory::playSoundEffect(multiKill);
        }
        else
        {

            int type;
            int id;
            GameFactory::property_list propertyList;


            in >> type;
            in >> id ;
            in >> propertyList;

            // 送给工厂
            GameFactory::createCommandRequestAndSend(command,
                                                     type,
                                                     id,
                                                     propertyList);


            //    emit signal_client_state("Post command to GameFactory!\r\n");

        }
        // reset next block size
        nextBlockSize = 0;
    }
}

// 客户端测试函数,请求服务器增加一个坦克
void PlayerClient::addOneBaseTank()
{
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly );

    int command =  GameFactory::CREATE;
    int type = GameFactory::BASE_TANK;
    int id = -1;
    GameFactory::property_list propertyList;
    propertyList << GameFactory::createPair("pos", QPointF(500, 300));

    stream << command ;
    stream << type;
    stream << id ;
    stream << propertyList;

    socket->write(array);
    socket->write("\n");
    socket->flush();
    emit signal_client_state("ask server to add one base tank!");
}


void PlayerClient::connectToServer(const QHostAddress& ip, qint16 port)
{
    qDebug() << ip.toString() << " " << port;
    socket->connectToHost(ip, port);
    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()),this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

void PlayerClient::writeKeyEventToServer(QKeyEvent *event)
{

    QString keyInfo = QString::number(event->type())
            + " "
            + QString::number(event->key())
            + " "
            + event->text();
    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly );

    int command =  GameFactory::KEY_EVENT;
    int type = event->type();
    int key = event->key();

    stream << qint16(0);

    stream << command;
    stream << type;
    stream << key;

    stream.device()->seek(0);
    stream << qint16(array.size() - sizeof qint16);

    socket->write(array);

    socket->flush();
    emit signal_client_state("write key event to server!\n" + keyInfo);
}

void PlayerClient::writeChatMessageToServer(QString message)
{
    // 增加信息

    QString date = QDate::currentDate().toString();
    QString time = QTime::currentTime().toString();

    message =  date + "\t" + time + "\n" + message;

    QByteArray array;
    QDataStream stream(&array, QIODevice::WriteOnly );

    stream << quint16(0);

    stream << GameFactory::CHAT ;


    stream << message;

    stream.device()->seek(0);
    stream << quint16(array.size() - sizeof(quint16));

    socket->write(array);

    socket->flush();
    qDebug() << "write message from client!";
}


