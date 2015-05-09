#ifndef PLAYERCLIENTVIEW_H
#define PLAYERCLIENTVIEW_H
// 客户端 与 服务器 连接界面, 客户端 tab2
#include <QWidget>
#include "playerclient.h"
namespace Ui {
class PlayerClientView;
}

class PlayerClientView : public QWidget
{
    Q_OBJECT
    
public:
    explicit PlayerClientView(QWidget *parent = 0);
    ~PlayerClientView();

    PlayerClient* getPlayerClient();
    
private slots:
    void on_connect_pushButton_clicked();

    void on_disconnect_pushButton_2_clicked();

    void on_pushButton_2_clicked();

    void on_send_pushButton_3_clicked();

private:
    Ui::PlayerClientView *ui;
    PlayerClient *playerclient;
};

#endif // PLAYERCLIENTVIEW_H
