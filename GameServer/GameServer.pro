######################################################################
# Automatically generated by qmake (3.0) ?? ?? 13 21:09:43 2013
######################################################################

QT       += core gui
QT += network
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GameServer
TEMPLATE = app

TEMPLATE = app
TARGET = GameServer
DEPENDPATH += . \
              clientrequestholder \
              gamefactory \
              gamegraphicsview \
              gamescene \
              gametcpserver \
              itemspool \
              serverview \
              items\bullet \
              items\mapelements \
              items\tank
INCLUDEPATH += .

# Input
HEADERS += clientrequestholder/clientrequestholder.h \
           gamefactory/gamefactory.h \
           gamegraphicsview/gamegraphicsview.h \
           gamescene/gamescene.h \
           gametcpserver/gametcpserver.h \
           gametcpserver/gametcpserverview.h \
           itemspool/itemspool.h \
           serverview/gameserver.h \
           items/bullet/basebullet.h \
           items/bullet/playerbullet.h \
           items/mapelements/basedestructiblemapelement.h \
           items/mapelements/basemapelement.h \
           items/mapelements/basesolidmapelement.h \
           items/mapelements/bounddeadlineelement.h \
           items/mapelements/boundlineelement.h \
           items/mapelements/brickmapelement.h \
           items/tank/basetank.h \
           items/tank/playertank.h
FORMS += gamegraphicsview/gamegraphicsview.ui \
         gametcpserver/tcpserver.ui \
         serverview/gameserver.ui
SOURCES += main.cpp \
           clientrequestholder/clientrequestholder.cpp \
           gamefactory/gamefactory.cpp \
           gamegraphicsview/gamegraphicsview.cpp \
           gamescene/gamescene.cpp \
           gametcpserver/gametcpserver.cpp \
           gametcpserver/gametcpserverview.cpp \
           itemspool/itemspool.cpp \
           serverview/gameserver.cpp \
           items/bullet/basebullet.cpp \
           items/bullet/playerbullet.cpp \
           items/mapelements/basedestructiblemapelement.cpp \
           items/mapelements/basemapelement.cpp \
           items/mapelements/basesolidmapelement.cpp \
           items/mapelements/bounddeadlineelement.cpp \
           items/mapelements/boundlineelement.cpp \
           items/mapelements/brickmapelement.cpp \
           items/tank/basetank.cpp \
           items/tank/playertank.cpp
RESOURCES += res.qrc
