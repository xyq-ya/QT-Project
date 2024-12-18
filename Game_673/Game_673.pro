QT       += core gui sql multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    game.cpp \
    main.cpp \
    musicplayer.cpp \
    widget.cpp

HEADERS += \
    database.h \
    game.h \
    musicplayer.h \
    widget.h

FORMS += \
    game.ui \
    widget.ui

TRANSLATIONS += \
    Game_673_zh_CN.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    image/1.png \
    image/10.png \
    image/11.png \
    image/12.png \
    image/13.png \
    image/14.png \
    image/15.png \
    image/16.png \
    image/17.png \
    image/18.png \
    image/19.png \
    image/2.png \
    image/20.png \
    image/21.png \
    image/22.png \
    image/23.png \
    image/24.png \
    image/25.png \
    image/3.png \
    image/4.png \
    image/5.png \
    image/6.png \
    image/7.png \
    image/8.png \
    image/9.png \
    sound/backgrand.mp3 \
    sound/pair.wav \
    sound/release.wav \
    sound/select.wav
