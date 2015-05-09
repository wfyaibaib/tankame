
#include "gamegraphicsview.h"

#include <QGraphicsItem>

#include <QDebug>
#include <QWheelEvent>

#include <QGraphicsItemAnimation>
#include <QTimeLine>

#include "./itemspool/itemspool.h"


GameGraphicsView::GameGraphicsView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gameGraphicsView)
{
    // view setting
    ui->setupUi(this);
    ui->graphicsView->setBackgroundBrush(QPixmap(":/res/cheese.jpg"));
    ui->graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorViewCenter);
    ui->graphicsView->setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);

    // create pool
    pool = new ItemsPool(this);




    // test music
   // GameFactory::playSoundEffect(GameFactory::KILL1);

    // setup scene for graphicsview
    ui->graphicsView->setScene(pool->getGameScene());

    // timer drive
    timer = new QTimer(this);
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()),
            pool->getGameScene(), SLOT(advance()));
    connect(timer, SIGNAL(timeout()),
            this, SLOT(on_countButton_clicked()));
    timer->start();

   //  testAnimation();

//    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
//                                             GameFactory::PLAYER_TANK,
//                                             -1,
//                                             GameFactory::property_list());

qDebug() << "GameGraphicsView ctor!";

}

GameGraphicsView::~GameGraphicsView()
{
    delete ui;
}

void GameGraphicsView::setFps(int fps)
{
    timer->setInterval(1000.0/fps);
}

void GameGraphicsView::addOneTank()
{
GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                         GameFactory::BASE_TANK,
                                         -1,
                                         GameFactory::property_list()
                                         << GameFactory::createPair("rotation", QVariant(qrand() % 360))
                                         << GameFactory::createPair("team", QVariant(qrand() % 4))
                                         );
//GameFactory::playSoundEffect(GameFactory::KILL1);

}

void GameGraphicsView::desOneTank()
{
    QList<QGraphicsItem*> list = pool->getGameScene()->items();

    // delete outside base_bullet and base_tank
    foreach (QGraphicsItem *item, list)
    {
        if ( (!pool->getGameScene()->sceneRect().contains(item->pos())) &&
              (item->type() == GameFactory::BASE_BULLET ||
               item->type() == GameFactory::BASE_TANK)
                )
        {
            pool->getGameScene()->removeItem(item);
        }
    }
}

void GameGraphicsView::itemRotate(int angle)
{
    auto list = pool->getGameScene()->selectedItems();
    if (list.isEmpty())
    {
        ui->graphicsView->rotate((angle + 0.0)  / 15);
        return;
    }
    foreach (QGraphicsItem* item, list)
    {

        //item->setTransformOriginPoint(item->boundingRect().center());
        auto obj = static_cast<QGraphicsObject*>(item);
        GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                 -1,
                                                 obj->objectName().toInt(),
                                                 GameFactory::property_list() <<
                                                 GameFactory::createPair("rotation",
                                                                         angle)
                                                 );

    }
}

void GameGraphicsView::wheelEvent(QWheelEvent *event)
{

     QList<QGraphicsItem*> list = pool->getGameScene()->selectedItems();
     if (list.isEmpty())
     {
         if ((event->angleDelta().y() > 0))
              ui->graphicsView->scale(1.1, 1.1);
         else
              ui->graphicsView->scale(0.9, 0.9);
     }
     if (event->angleDelta().y() > 0)
     {
         foreach (QGraphicsItem *item, list)
         {
             auto obj = static_cast<QGraphicsObject*>(item);
             GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                      -1,
                                                      obj->objectName().toInt(),
                                                      GameFactory::property_list() <<
                                                      GameFactory::createPair("scale",
                                                                              obj->property("scale").toReal() * 1.1)
                                                      );
         }
     }
     else
     {
         foreach (QGraphicsItem *item, list)
         {
             auto obj = static_cast<QGraphicsObject*>(item);
             GameFactory::createCommandRequestAndSend(GameFactory::SET_PROPERTY,
                                                      -1,
                                                      obj->objectName().toInt(),
                                                      GameFactory::property_list() <<
                                                      GameFactory::createPair("scale",
                                                                              obj->property("scale").toReal() * 0.9)
                                                      );
         }
     }
}

void GameGraphicsView::testAnimation()
{

//    QGraphicsPixmapItem *kill1 = new QGraphicsPixmapItem();
//    kill1->setPixmap(QPixmap(":/res/kill4.png"));
//    kill1->setFlag(QGraphicsItem::ItemIsSelectable);
//    kill1->setFlag(QGraphicsItem::ItemIsMovable);


//    QTimeLine *timer_ = new QTimeLine(5000);
//    timer_->setParent(this);

//    timer_->setFrameRange(0, 100);

//    QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
//    animation->setItem(kill1);
//    animation->setTimeLine(timer_);

//    for (int i = 0; i < 200; ++i)
//        animation->setPosAt(i / 200.0, QPointF(-400 + i,-400 + i));



//    scene->addItem(kill1);

//    timer_->start();
}


void GameGraphicsView::on_countButton_clicked()
{
    QList<QGraphicsItem*> list = pool->getGameScene()->items();
    int selected = 0;
    foreach (QGraphicsItem* item, list)
    {
        if (item->isSelected())
            ++selected;
    }
    ui->countButton->setText(QString::number(list.count()) + ":" +
                             QString::number(selected));

}

void GameGraphicsView::on_pushButton_3_clicked()
{
    // 增加 死亡边界线
    int x = -200;
    int y = 0;
    int width = 1000;
    int height = 600;
    // top
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_DEAD_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x, y)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(0))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(width))


                                             );
    // left
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_DEAD_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x, y)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(90))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(height))

                                             );
    // bottom
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_DEAD_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x + width, y + height)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(180))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(width))

                                             );
    // right
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_DEAD_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x + width, y + height)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(270))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(height))

                                             );

    // 增加 边界线
    int x1 = x + 10;
    int y1 = y + 10;
    int width1 = width - 20;
    int height1 = height - 20;
    // top
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x1, y1)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(0))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(width1))


                                             );
    // left
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x1, y1)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(90))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(height1))

                                             );
    // bottom
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x1 + width1, y1 + height1)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(180))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(width1))

                                             );
    // right
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BOUND_LINE,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos",
                                                                     QVariant(QPointF(x1 + width1, y1 + height1)))
                                             <<
                                             GameFactory::createPair("rotation",
                                                                     QVariant(270))
                                             <<
                                             GameFactory::createPair("lineLength",
                                                                     QVariant(height1))

                                             );

}

void GameGraphicsView::on_pushButton_4_clicked()
{
    // brick map element
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::BRICK_ELEMENT,
                                             -1,
                                             GameFactory::property_list()
                                             <<
                                             GameFactory::createPair("pos", QPointF(0, 0)));

}

void GameGraphicsView::on_pushButton_5_clicked()
{
    // add player tank
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::PLAYER_TANK,
                                             -1,
                                             GameFactory::property_list());
}
