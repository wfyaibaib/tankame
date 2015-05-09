#ifndef GAMECLIENTVIEW_H
#define GAMECLIENTVIEW_H

#include <QWidget>
#include "./gamefactory/gamefactory.h"
#include "./itemspool/itemspool.h"
// 客户端整体界面
// tab1 游戏界面, tab2 网络连接界面
namespace Ui {
class GameClientView;
}

class GameClientView : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameClientView(QWidget *parent = 0);
    ~GameClientView();
    
private:
    Ui::GameClientView *ui;
    ItemsPool *pool;
};

#endif // GAMECLIENTVIEW_H
