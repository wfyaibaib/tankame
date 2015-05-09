#include "gametcpserverview.h"
#include <QTcpSocket>
#include "ui_tcpserver.h"

GameTcpServerView::GameTcpServerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpServer)
{
   ui->setupUi(this);
   server = new GameTcpServer(this);

   connect(server, SIGNAL(signal_state(QString)),
           ui->plainTextEdit, SLOT(appendPlainText(QString)));
   connect(server, SIGNAL(signal_serverPostChatMessageToAllClient(QString)),
           ui->plainTextEdit, SLOT(appendPlainText(QString)));
}
GameTcpServerView::~GameTcpServerView()
{
    delete ui;
}

void GameTcpServerView::on_pushButton_2_clicked()
{
    int port = ui->port_spinBox->value();
    server->startServer(port);
    ui->pushButton_2->setEnabled(false);
    ui->pushButton_3->setEnabled(true);

}

void GameTcpServerView::on_pushButton_3_clicked()
{
    server->close();
    ui->pushButton_2->setEnabled(true);
    ui->pushButton_3->setEnabled(false);

}
