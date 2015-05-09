#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include "./gamefactory/gamefactory.h"
#include "./items/tank/basetank.h"
#include <QTimer>

#include <QObject>

// 玩家坦克类
class PlayerTank : public BaseTank
{
  Q_OBJECT
public:
    Q_INVOKABLE PlayerTank();
    virtual void doCollision();
    virtual void fire();
    virtual void advance(int phase);

    void processKeyEvent(QKeyEvent *event);

    int type() const;
signals:

protected:
    void keyPressEvent(QKeyEvent *event);
private:
    QTimer *multi_kill_timer;
    int     multi_kill_count_flags;
private slots:
    void shift_right();
    void kill_one();

};

#endif // PLAYERTANK_H
