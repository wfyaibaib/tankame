#ifndef SIMPLEGRAPHICVIEW_H
#define SIMPLEGRAPHICVIEW_H

#include <QWidget>
#include <QTimer>

#include "./gamefactory/gamefactory.h"
#include "./itemspool/itemspool.h"

#include "ui_gamegraphicsview.h"// ui

namespace Ui {
class gameGraphicsView;
}

class GameGraphicsView : public QWidget
{
    Q_OBJECT
    
public:
    explicit GameGraphicsView(QWidget *parent = 0);
    ~GameGraphicsView();


public slots:
    void setFps(int fps);
    void addOneTank();
    void desOneTank();
    void itemRotate(int angle);
private slots:
    void on_countButton_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

protected:
    void wheelEvent(QWheelEvent * event);

    void testAnimation();

private:
    Ui::gameGraphicsView *ui;

    QTimer * timer;
    ItemsPool* pool;
};

#endif // SIMPLEGRAPHICVIEW_H
