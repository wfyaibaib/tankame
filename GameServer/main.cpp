#include "./serverview/gameserver.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameServer w;
    w.show();
    
    return a.exec();
}
