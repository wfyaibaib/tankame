#ifndef GAMEFACTORY_H
#define GAMEFACTORY_H

#include <QObject>
#include <QGraphicsObject>
#include <QDebug>
#include <QSoundEffect>
#include <QPixmap>
#include <bitset>
#include <QHash>
#include <QGraphicsScene>

#include <QPair>
#include <QString>
#include <QByteArray>
#include <QMetaObject>


class GameTcpServer;

class BaseBullet;
class BaseTank;
class ItemsPool;

class QKeyEvent;

class GameFactory : public QObject
{
    Q_OBJECT
public:
    explicit GameFactory(QObject *parent = 0);
/*******************************************************************************/

/*******************************************************************************/

  // 图元类型枚举
    enum type_enum {
        GAME_TYPE = QGraphicsItem::UserType,// 0x 0001 0000

        ALL_MASK = 0xFFFFFFFF,

        // tank
        TANK_MASK =            0x00011000,
        BASE_TANK =            TANK_MASK,
        PLAYER_TANK =          TANK_MASK    | 0x1,

        // bullet
        BULLET_MASK =          0x00012000,
        BASE_BULLET =          BULLET_MASK,
        PLAYER_BULLET =        BULLET_MASK   | 0x1,

        // map_element
        MAP_ELEMENT_MASK =     0x00014000,
        BOUND_LINE       =     MAP_ELEMENT_MASK  | 0x1,
        BOUND_DEAD_LINE  =     BOUND_LINE                 | 0x10,
        BRICK_ELEMENT    =     MAP_ELEMENT_MASK  | 0x2

    };

/*******************************************************************************/
    // 游戏音效
    enum sound_enum {

        KILL1 = 1,
        KIll2,
        KILL3,
        KILL4,

        DIE_SOUND = 256,
        MOVE_SOUND,
        FIRE_SOUND,
        PLAYER_DIE,
        CRASH_DIE_SOUND
    };

    static  QSoundEffect tankMoveSound;
    static  QSoundEffect tankDieSound;
    static  QSoundEffect tankCrashDieSound;

    static  QSoundEffect tankKill1Sound;
    static  QSoundEffect tankKill2Sound;
    static  QSoundEffect tankKill3Sound;
    static  QSoundEffect tankKill4Sound;

    static void playSoundEffect(sound_enum sound_type);
    static void setupSoundEffect();

/*******************************************************************************/
    // 队伍枚举
    enum tank_team_enum{
                        //32 bit 相与为0,则不在一个队伍中

                        };

/*******************************************************************************/
    // 请求命令字
    enum command_enum{

        MULTI_KILL = -2,

        KEY_EVENT = -1,
        CHAT,
        CREATE = 1,
        DELETE,
        SET_PROPERTY
    };
    typedef QPair<QByteArray, QVariant> propery_value_pair;
    typedef QList<propery_value_pair> property_list;
    static propery_value_pair createPair(QByteArray name, QVariant value)
    {
        return qMakePair(name, value);
    }
/*******************************************************************************/
    // socket 描述符映射到 玩家坦克Id
    static QHash<int, int> socketDescriptorTankIdHash;
    static void postKeyEventToPlayerTankBySocketDescriptor(int descriptor, QKeyEvent* event);
    static int addPlayerTankBySocketDescriptor(int descriptor);
/*******************************************************************************/

/*******************************************************************************/

    // 请求作用属性
    enum property_change_enum{

        GAME_PROPERY_CHANGE     = 0x00010000,
        POSITION                = GAME_PROPERY_CHANGE |   0x1,
        SCALE                   = GAME_PROPERY_CHANGE |   0x2,
        ROTATION                = GAME_PROPERY_CHANGE |   0x4
    };

    // 命令请求格式
    struct GameCommandRequest
    {
        int  command;           // command_enum: 操作类型
        int     type;              // type_enum   : 操作对象类别
        int           id;                // int           操作对象ID
        property_list  propertyList;      //

    };
    // 创建请求

    static void createCommandRequestAndSend(int command,
                                      int    type,
                                      int          id,
                                      property_list propertyList);
    static int getNextUnusedIdFromPool();
    static QGraphicsObject* getGraphicsObjectFromPoolById(int id);
/*******************************************************************************/

    // 创建图元
    static QGraphicsObject* createGraphicsObject(int type);

/*******************************************************************************/
    // 图元类型辅助
    static bool twoItemsHaveSameFlags(QGraphicsItem *item1,
                             QGraphicsItem *item2,
                             type_enum maskflags = ALL_MASK);
    static bool twoTanksHaveSameTeam(QGraphicsItem *tank1,
                                QGraphicsItem *tank2);
    static bool oneItemHaveFlags(QGraphicsItem *item, type_enum maskflags);

/*******************************************************************************/
      static QHash<int, QMetaObject> knownClasses;
      static void setupInternalClasses();
      static void addNewClass(type_enum type, QMetaObject metaobject);
/*******************************************************************************/

      static ItemsPool *pool;
      static void setupPool(ItemsPool *pool_);
      static ItemsPool *getPool();
/*******************************************************************************/
      static GameTcpServer *server;
      static void setupServer(GameTcpServer* server_);
      static GameTcpServer *getTcpServer();

      static void writeMultiKillCommandToSocketByPlayerTankId(int playerTankId, int multiKill);

signals:
    
public slots:
    
};


#endif // GAMEFACTORY_H
