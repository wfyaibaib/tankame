#include "gameclientview.h"
#include "ui_gameclientview.h"
#include "./clientgraphicsview/clientgraphicsview.h"
//
GameClientView::GameClientView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameClientView)
{
    ui->setupUi(this);

    // create pool
    pool = new ItemsPool(this);
    // game factory post request from server to pool
    GameFactory::setupPool(pool);
    GameFactory::setupInternalClasses();
    GameFactory::setupSoundEffect();
    // setup scene
    ui->graphicsView->setScene(pool->getGameScene());
    ui->graphicsView->setBackgroundBrush(QPixmap(":/res/cheese.jpg"));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    // 玩家在graphicsview上的按键
    connect(ui->graphicsView, SIGNAL(signal_getKeyEventFromPlayer(QKeyEvent*)),
            ui->clientNetwork_widget->getPlayerClient(), SLOT(writeKeyEventToServer(QKeyEvent*)));

}

GameClientView::~GameClientView()
{
    delete ui;
}
