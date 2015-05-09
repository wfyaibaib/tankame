#include "playerclientview.h"
#include "ui_playerclientview.h"
#include <QHostAddress>
PlayerClientView::PlayerClientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlayerClientView)
{
    ui->setupUi(this);
    playerclient  =  new PlayerClient(this);
    connect(playerclient, SIGNAL(signal_client_state(QString)),
            ui->plainTextEdit, SLOT(appendPlainText(QString)));
    connect(playerclient, SIGNAL(signal_get_chat_message_from_server(QString)),
            ui->chatRecord_plainTextEdit_2, SLOT(appendPlainText(QString)));


}

PlayerClientView::~PlayerClientView()
{
    delete ui;
}

PlayerClient *PlayerClientView::getPlayerClient()
{
    return playerclient;
}

void PlayerClientView::on_connect_pushButton_clicked()
{
    QString ips = ui->ip_lineEdit->text();
    QHostAddress ip(ips);
    playerclient->connectToServer(ip, ui->port_spinBox->value());
}

void PlayerClientView::on_disconnect_pushButton_2_clicked()
{
    playerclient->closeConnect();
}

void PlayerClientView::on_pushButton_2_clicked()
{
    playerclient->addOneBaseTank();
}

void PlayerClientView::on_send_pushButton_3_clicked()
{
    QString need_send = ui->chatInput_plainTextEdit_3->toPlainText();
    ui->chatInput_plainTextEdit_3->clear();
    if (!need_send.isEmpty())
    {
        playerclient->writeChatMessageToServer(need_send);

    }
}
