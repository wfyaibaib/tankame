#include "gamefactory.h"
#include "./itemspool/itemspool.h"
#include <QUrl> // for sound effect
/*******************************************************************************/
#include "./items/tank/basetank.h"
#include "./items/tank/playertank.h"
/*******************************************************************************/
#include "./items/bullet/basebullet.h"
#include "./items/bullet/playerbullet.h"
/*******************************************************************************/
#include "./items/mapelements/boundlineelement.h"
#include "./items/mapelements/bounddeadlineelement.h"
#include "./items/mapelements/brickmapelement.h"
/*******************************************************************************/
#include "./gametcpserver/gametcpserver.h"
#include <QCoreApplication>// post event to tank
// 服务器图元工厂
/*******************************************************************************/
GameFactory::GameFactory(QObject *parent) :
    QObject(parent)
{
}
/*******************************************************************************/
// 元对象
QHash<int, QMetaObject> GameFactory::knownClasses;
void GameFactory::setupInternalClasses()
{
    knownClasses[GameFactory::BASE_BULLET] = BaseBullet::staticMetaObject;
    knownClasses[GameFactory::PLAYER_BULLET] = PlayerBullet::staticMetaObject;

    knownClasses[GameFactory::BASE_TANK] = BaseTank::staticMetaObject;
    knownClasses[GameFactory::PLAYER_TANK] = PlayerTank::staticMetaObject;

    knownClasses[GameFactory::BOUND_LINE] = BoundLineElement::staticMetaObject;
    knownClasses[GameFactory::BOUND_DEAD_LINE] = BoundDeadLineElement::staticMetaObject;
    knownClasses[GameFactory::BRICK_ELEMENT] = BrickMapElement::staticMetaObject;

    qDebug() << "GameFactory::setupInternalClasses()";
}
/*******************************************************************************/
void GameFactory::addNewClass(GameFactory::type_enum type, QMetaObject metaobject)
{
    knownClasses[type] = metaobject;
}
/*******************************************************************************/
/*******************************************************************************/
// 游戏音效
QSoundEffect GameFactory::tankMoveSound;
QSoundEffect GameFactory::tankDieSound;
QSoundEffect GameFactory::tankCrashDieSound;

QSoundEffect GameFactory::tankKill1Sound;
QSoundEffect GameFactory::tankKill2Sound;
QSoundEffect GameFactory::tankKill3Sound;
QSoundEffect GameFactory::tankKill4Sound;

void GameFactory::setupSoundEffect()
{
    static bool already_setup = false;
    if (already_setup) return;
    qDebug() << "setup sound effect!";
    tankDieSound.setSource(QUrl::fromLocalFile((":/res/die_bomb.WAV")));
    tankCrashDieSound.setSource(QUrl::fromLocalFile((":/res/oh_no.wav")));

    tankKill1Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_1_CT.wav"));
    tankKill2Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_2_CT.wav"));
    tankKill3Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_3_CT.wav"));
    tankKill4Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_4_CT.wav"));

    already_setup = true;
}
void GameFactory::playSoundEffect(GameFactory::sound_enum sound_type)
{
    //


    setupSoundEffect();
    qDebug() << "sound " << sound_type;
    switch (sound_type)
    {
    case KILL1:
      qDebug() << "play!";
        tankKill1Sound.play();
        qDebug() << "sound 1 over!";
        break;
    case KIll2:
       tankKill2Sound.play();
        break;
    case KILL3:
        tankKill3Sound.play();
        break;
    case KILL4:
        tankKill4Sound.play();
        break;
    case DIE_SOUND:
         qDebug() << "die sound!";
        tankDieSound.play();
          qDebug() << "die sound over!";
        break;
    case PLAYER_DIE:
        break;
    case MOVE_SOUND:
        break;
    case FIRE_SOUND:
        break;
    case CRASH_DIE_SOUND:
        tankCrashDieSound.play();
        break;
    }
}
/*******************************************************************************/
QHash<int, int> GameFactory::socketDescriptorTankIdHash;
void GameFactory::postKeyEventToPlayerTankBySocketDescriptor(int descriptor,
                                                             QKeyEvent *event)
{
    // 查找玩家坦克ID
    int tankId = -1;
    if (socketDescriptorTankIdHash.contains(descriptor))
    {
        tankId = socketDescriptorTankIdHash[descriptor];
    }
    //
    if ( -1 != tankId)
    {

        QGraphicsItem *tankItem = getPool()->getItemById(tankId);
        if (tankItem && tankItem->type() == GameFactory::PLAYER_TANK)
        {// 对象池有此对象,并是坦克

            PlayerTank *tank = static_cast<PlayerTank*>(tankItem);
            tank->processKeyEvent(event);

            qDebug() << "event post to tank!";
        }
        else
        {

        }

    }
}
int GameFactory::addPlayerTankBySocketDescriptor(int descriptor)
{
    int newId = getPool()->getNextUnusedId();
    GameFactory::createCommandRequestAndSend(GameFactory::CREATE,
                                             GameFactory::PLAYER_TANK,
                                             -1,
                                             GameFactory::property_list());
    socketDescriptorTankIdHash[descriptor] = newId;
    qDebug() << "addPlayerTankBySocketDescriptor : descriptor = " << descriptor;
    return newId;

}
/*******************************************************************************/

/*******************************************************************************/

// 辅助类型判断
bool GameFactory::twoItemsHaveSameFlags(QGraphicsItem *item1,
                               QGraphicsItem *item2,
                               GameFactory::type_enum maskflags)
{
    return (item1->type() & maskflags) == (item2->type() & maskflags);
}

bool GameFactory::twoTanksHaveSameTeam(QGraphicsItem *tank1, QGraphicsItem *tank2)
{
    Q_ASSERT(twoItemsHaveSameFlags(tank1, tank2, BASE_TANK));
    return static_cast<BaseTank*>(tank1)->getTeam() &
            static_cast<BaseTank*>(tank2)->getTeam();
}

bool GameFactory::oneItemHaveFlags(QGraphicsItem *item, GameFactory::type_enum maskflags)
{
    return maskflags == (item->type() & maskflags);
}
/*******************************************************************************/

ItemsPool* GameFactory::pool;
void GameFactory::setupPool(ItemsPool *pool_)
{
    pool = pool_;
    qDebug() << "GameFactory::setupPool(ItemsPool *pool_)";
}

ItemsPool *GameFactory::getPool()
{
    return pool;
}
/*******************************************************************************/
GameTcpServer* GameFactory::server;
void GameFactory::setupServer(GameTcpServer *server_)
{
    server = server_;
}
GameTcpServer* GameFactory::getTcpServer()
{
    return server;
}

void GameFactory::writeMultiKillCommandToSocketByPlayerTankId(int playerTankId, int multiKill)
{
    qDebug() << "write Multi kill by tank id";
    // query socket descriptor
    int socketId = socketDescriptorTankIdHash.key(playerTankId);
    // ask tcp server to post request to the client
    getTcpServer()->askOneClientRequestHolderToPostMultiKillEffectToPlayerBySocketDescriptor(socketId,
                                                                                             multiKill);

}


/*******************************************************************************/
// 命令格式
void GameFactory::createCommandRequestAndSend(
        int command,
        int type,
        int          id,
        property_list propertyList
      )
{
    GameFactory::GameCommandRequest request;
    request.command = command;
    request.type = type;
    request.id = id;
    request.propertyList = propertyList;
    getPool()->processRequest(request);
}

int GameFactory::getNextUnusedIdFromPool()
{
     return getPool()->getNextUnusedId();
}

QGraphicsObject *GameFactory::getGraphicsObjectFromPoolById(int id)
{
    return static_cast<QGraphicsObject*>(getPool()->getItemById(id));
}

// 枚举所有图元类型
QGraphicsObject *GameFactory::createGraphicsObject(int type)
{
    QGraphicsObject *newGraphicsObject = 0;
    if (knownClasses.contains(type))
    {
        const QMetaObject& mo = knownClasses[type];
        newGraphicsObject = static_cast<QGraphicsObject*>(mo.newInstance());
        return newGraphicsObject;
    }
    else
    {
        return 0;
    }
}

/*******************************************************************************/
