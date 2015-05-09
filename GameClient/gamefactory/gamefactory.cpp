#include "./gamefactory/gamefactory.h"
#include <QUrl>
#include "./items/tank/basetank.h"
#include "./items/bullet/basebullet.h"
#include "./items/tank/playertank.h"
#include "./items/mapelements/boundlineelement.h"
#include "./items/bullet/playerbullet.h"
#include "./items/mapelements/bounddeadlineelement.h"
#include <QGraphicsView>
#include "./itemspool/itemspool.h"
/*******************************************************************************/
GameFactory::GameFactory(QObject *parent) :
    QObject(parent)
{

}

//void GameFactory::setupItemsPool(ItemsPool *pool)
//{
//}

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

    tankDieSound.setSource(QUrl::fromLocalFile((":/res/die_bomb.WAV")));
    tankCrashDieSound.setSource(QUrl::fromLocalFile((":/res/oh_no.wav")));

    tankKill1Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_1_CT.wav"));
    tankKill2Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_2_CT.wav"));
    tankKill3Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_3_CT.wav"));
    tankKill4Sound.setSource(QUrl::fromLocalFile(":/res/MultiKill_4_CT.wav"));

    already_setup = true;
}

void GameFactory::playSoundEffect(int sound_type)
{
    setupSoundEffect();
    qDebug() << "sound " << sound_type;
    switch (sound_type)
    {
    case KILL1:
 //       qDebug() << "play!";
        tankKill1Sound.play();
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
  //      qDebug() << "die sound!";
        tankDieSound.play();
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
/*******************************************************************************/
QHash<int, QMetaObject> GameFactory::knownClasses;
void GameFactory::setupInternalClasses()
{
    knownClasses[GameFactory::BASE_BULLET] = BaseBullet::staticMetaObject;
    knownClasses[GameFactory::BASE_TANK] = BaseTank::staticMetaObject;
    knownClasses[GameFactory::PLAYER_TANK] = PlayerTank::staticMetaObject;
    knownClasses[GameFactory::PLAYER_BULLET] = PlayerBullet::staticMetaObject;
    knownClasses[GameFactory::BOUND_DEAD_LINE] = BoundDeadLineElement::staticMetaObject;
    knownClasses[GameFactory::BOUND_LINE] = BoundLineElement::staticMetaObject;
}
/*******************************************************************************/
void GameFactory::addNewClass(GameFactory::type_enum type, QMetaObject metaobject)
{
    knownClasses[type] = metaobject;
}
/*******************************************************************************/
ItemsPool* GameFactory::pool;
void GameFactory::setupPool(ItemsPool *pool_)
{
    pool = pool_;
}

ItemsPool *GameFactory::getPool()
{
    return pool;
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
