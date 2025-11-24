QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bullet.cpp \
    cloud.cpp \
    connon1.cpp \
    connon3.cpp \
    dred_block.cpp \
    enemy_plane.cpp \
    losescene.cpp \
    main.cpp \
    mainscene.cpp \
    map.cpp \
    mcard.cpp \
    mshop.cpp \
    mypushbotton.cpp \
    red_block.cpp \
    startscene.cpp \
    wheel.cpp \
    winscene.cpp

HEADERS += \
    bullet.h \
    cloud.h \
    config.h \
    connon1.h \
    connon3.h \
    dred_block.h \
    enemy_plane.h \
    losescene.h \
    mainscene.h \
    map.h \
    mcard.h \
    mshop.h \
    mypushbotton.h \
    red_block.h \
    startscene.h \
    wheel.h \
    winscene.h

FORMS += \
    mainscene.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res.qrc
