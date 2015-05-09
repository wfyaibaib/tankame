#ifndef GAMESERVER_H
#define GAMESERVER_H

#include <QWidget>

namespace Ui {
class GameServer;
}

class GameServer : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameServer(QWidget *parent = 0);
    ~GameServer();
    
private:
    Ui::GameServer *ui;
};

#endif // GAMESERVER_H
