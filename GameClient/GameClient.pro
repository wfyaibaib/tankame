######################################################################
# Automatically generated by qmake (3.0) ?? ?? 13 18:10:47 2013
######################################################################

QT       += core gui
QT += network
QT += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = GameClient
DEPENDPATH += . \
              clientgraphicsview \
              clientview \
              gamefacotry \
              gamescene \
              itemspool \
              net \
              items\bullet \
              items\mapelements \
              items\tank
INCLUDEPATH += .

# Input
HEADERS += clientgraphicsview/clientgraphicsview.h \
           clientview/gameclientview.h \
           gamefactory/gamefactory.h \
           gamescene/gamescene.h \
           itemspool/itemspool.h \
           net/playerclient.h \
           net/playerclientview.h \
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
FORMS += clientview/gameclientview.ui \
         net/playerclientview.ui
SOURCES += main.cpp \
           clientgraphicsview/clientgraphicsview.cpp \
           clientview/gameclientview.cpp \
           gamefactory/gamefactory.cpp \
           gamescene/gamescene.cpp \
           itemspool/itemspool.cpp \
           net/playerclient.cpp \
           net/playerclientview.cpp \
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
