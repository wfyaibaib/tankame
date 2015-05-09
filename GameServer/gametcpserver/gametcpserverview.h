#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include <QTcpServer>
#include <QThreadPool>
#include "gametcpserver.h"
// 游戏服务器界面
namespace Ui {
class TcpServer;
}

class GameTcpServerView : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameTcpServerView(QWidget *parent = 0);
    ~GameTcpServerView();
signals:
    void signal_getString(QString s);
protected:

    
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::TcpServer *ui;
    GameTcpServer* server;

};

#endif // TCPSERVER_H
