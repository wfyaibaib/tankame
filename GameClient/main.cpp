#include "./clientview/gameclientview.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    GameClientView w;
    w.show();
    
    return a.exec();
}
