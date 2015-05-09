#ifndef ITEMSPOOL_H
#define ITEMSPOOL_H

#include <QObject>
#include "./gamefactory/gamefactory.h"
#include "./gamescene/gamescene.h"
/*
 *服务器端:所有图元有时钟驱动,图元按自己规则,向工厂发送请求,创建删除更改属性,工厂转发给对象池
 *对象池执行请求,并发送此命令到各游戏客户端对象池
 *
 *游戏客户端图元无时钟驱动,对象接收服务器端对象池命令,在自己对象池中执行此命令,保证两个对象池一致性
 *
 *游戏客户端玩家操作封装成请求,发送给服务器,服务器对象池执行后再广播给所有玩家
 *
 *
 *
 *
 *
 *
 *
 */
class ItemsPool : public QObject
{
    Q_OBJECT
    friend class GameFactory;
public:
/*******************************************************************************/
   // 设置某个对象某属性值,无对象返回false
    bool setPropertyById(int id, const GameFactory::property_list &list);

   // 向pool中增加一个对象,参数: 对象类型
   int addItemByType(int type);

   // 向pool中删除一个对象
   bool removeItemById(int id);

   //
   GameScene *getGameScene();
/*******************************************************************************/
public:
    explicit ItemsPool(QObject *parent = 0);
    void printAllItems();
    
signals:
   void signal_NewCommand(GameFactory::GameCommandRequest command);
   void signal_PostCommandToNetwork(GameFactory::GameCommandRequest command);
    
public slots:
   void processRequest(GameFactory::GameCommandRequest &command);

private:
   enum server_or_client_enum { SERVER, CLIENT };
   server_or_client_enum server_or_client;

   GameScene *scene;
/*******************************************************************************/
   std::bitset<1024> used_flags;
   // 对象id 到 地址
   QHash<int, QGraphicsItem*> graphicsItemsHash;
   // 得到一个空闲序号
   int getNextUnusedId();
   int getUnusedIdAndSet();
   // 由id 得到一个对象
   QGraphicsItem *getItemById(int id);
   template <class bitset_type>
   static int getLast0bitIndex(bitset_type bitset)
   {
       if (bitset.all()) return -1;
       for(int i = 0; i < bitset.size(); ++i)
       {
           if (!bitset[i]) return i;
       }
   }
/*******************************************************************************/
    
};

#endif // ITEMSPOOL_H
