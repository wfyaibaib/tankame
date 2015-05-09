#include "gameserver.h"
#include "ui_gameserver.h"

GameServer::GameServer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameServer)
{
    ui->setupUi(this);
    qDebug() << "GameServer ctor!";
}

GameServer::~GameServer()
{
    delete ui;
}
