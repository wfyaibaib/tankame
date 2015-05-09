#include "itemspool.h"
#include <QGraphicsView>
#include <QDebug>
#include <QMetaProperty>
/*******************************************************************************/
ItemsPool::ItemsPool(QObject *parent) :
    QObject(parent)
{
    scene = new GameScene(this);
    server_or_client = SERVER;

    GameFactory::setupPool(this);
    // init factory
    GameFactory::setupInternalClasses();
    GameFactory::setupSoundEffect();

    qDebug() << "pool ctor!";
}
//
GameScene *ItemsPool::getGameScene()
{
    return scene;
}
/*******************************************************************************/
// 由图元类型加入,对外接口
int ItemsPool::addItemByType(int type)
{
    QGraphicsObject *newItem = GameFactory::createGraphicsObject(type);
    int id = getUnusedIdAndSet();
    if (id != -1)
    {
        graphicsItemsHash[id] = newItem;
        newItem->setObjectName(QString::number(id));
        scene->addItem(newItem);
      //  qDebug() << id << " added!" ;
    }
    return id;
}
// 由图元id删除,对外接口
bool ItemsPool::removeItemById(int id)
{
    if (graphicsItemsHash.contains(id))
    {
        used_flags[id] = false;
        QGraphicsItem *item = graphicsItemsHash[id];
        item->setVisible(false);
        static_cast<QGraphicsObject*>(item)->deleteLater();

        graphicsItemsHash.remove(id);

        return true;
    }
    return false;
}
// 设置图元属性,对外接口
bool ItemsPool::setPropertyById(int id,
                                const GameFactory::property_list &list)
{
  //   qDebug() << "setProperyById: id = " << id << " "<< list;
    auto *item_object = static_cast<QGraphicsObject*>(getItemById(id));

    if (!item_object)
    {
        return false;
    }
    else
    {
        foreach (GameFactory::propery_value_pair pair, list )
        {
            if(!item_object->setProperty(pair.first, pair.second))
            {
                return false;
            }
        }
    }
     return true;

}
/*******************************************************************************/
// 得到空闲id
int ItemsPool::getUnusedIdAndSet()
{
    int unusedIndex = getLast0bitIndex(used_flags);
    if (unusedIndex == -1) return -1;
    else
    {
        used_flags[unusedIndex] = true;
        return unusedIndex;
    }
}
// 由id得到图元
QGraphicsItem *ItemsPool::getItemById(int id)
{
    if (graphicsItemsHash.contains(id))
        return graphicsItemsHash.value(id);
    return 0;
}

/*******************************************************************************/
// 命令请求处理,创建,销毁,设置图元属性
void ItemsPool::processRequest(GameFactory::GameCommandRequest&
                               command_request)
{
   /*
    static int cnt = 0;
    qDebug() << "Request:\t" << ++cnt << endl
             <<"\tcommand:\t" << command_request.command << endl
            <<"\tid:\t" << command_request.id << endl
             << "\ttype:\t" << command_request.type << endl
             << "\tproperty:\t" << command_request.propertyList;
    */

    switch (command_request.command)
    {
    // 由类型创建一个对象,并设置属性
    case GameFactory::CREATE:
         command_request.id = addItemByType(command_request.type);
         setPropertyById(command_request.id, command_request.propertyList);
        // qDebug() << "------------------create: id = " << command_request.id;
         break;
    // 由id 删除一个对象
    case GameFactory::DELETE:
         this->removeItemById(command_request.id);
        // qDebug() << "=================remove: id = " << command_request.id;
         break;
    // 设置一个对象的属性
    case GameFactory::SET_PROPERTY:
        setPropertyById(command_request.id,
                        command_request.propertyList);
        break;
    }
    // 对外广播信号
    emit signal_PostCommandToNetwork(command_request);
}

int ItemsPool::getNextUnusedId()
{
    return  getLast0bitIndex(used_flags);
}

void ItemsPool::printAllItems()
{
    QGraphicsObject *itemObj = 0;
    foreach (QGraphicsItem* item, this->getGameScene()->items())
    {

        if (itemObj = dynamic_cast<QGraphicsObject*>(item))
        {
            qDebug() << "graphics_object:" << endl
                    <<  "id = " << itemObj->objectName() << endl

                   << "type = " << itemObj->type() << endl
                   << "classname = " << itemObj->metaObject()->className() << endl
                   << "scale = " << itemObj->scale() << endl
                   << "pos = " << itemObj->pos() << endl
                    << "rotation = "<< itemObj->rotation();

            auto metaObject = itemObj->metaObject();
            for(int i = metaObject->propertyOffset(); i < metaObject->propertyCount(); ++i)
            {
                auto name = metaObject->property(i).name();
                qDebug() << metaObject->property(i).name()
                         << " : "
                         << itemObj->property(name);
            }

        }
    }
}
