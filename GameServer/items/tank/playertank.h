#ifndef PLAYERTANK_H
#define PLAYERTANK_H

#include "./gamefactory/gamefactory.h"
#include "basetank.h"
#include <QTimer>

#include <QObject>

class PlayerTank : public BaseTank
{
  Q_OBJECT
public:
    Q_INVOKABLE PlayerTank();
    virtual void doCollision();
    virtual void fire();
    virtual void advance(int phase);

    int type() const;
    void processKeyEvent(QKeyEvent *event);
signals:
protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    QTimer *multi_kill_timer;
    int     multi_kill_count_flags;

    bool up;
    bool left;
    bool right;
    bool down;
    bool firing;

public slots:
    void shift_right();
    void kill_one();
};

#endif // PLAYERTANK_H
