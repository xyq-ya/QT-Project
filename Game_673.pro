QT       += core gui sql multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    database.cpp \
    degreeofdifficulty.cpp \
    game.cpp \
    main.cpp \
    menu.cpp \
    musicplayer.cpp \
    splashscreen.cpp \
    victory.cpp \
    widget.cpp

HEADERS += \
    database.h \
    degreeofdifficulty.h \
    game.h \
    menu.h \
    musicplayer.h \
    splashscreen.h \
    victory.h \
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
    image/1d.png \
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
    image/back1.png \
    image/back2.png \
    image/back3.png \
    image/obstacle.jpg \
    image/shadow/1.png \
    image/shadow/10.png \
    image/shadow/11.png \
    image/shadow/12.png \
    image/shadow/13.png \
    image/shadow/14.png \
    image/shadow/15.png \
    image/shadow/16.png \
    image/shadow/17.png \
    image/shadow/18.png \
    image/shadow/19.png \
    image/shadow/2.png \
    image/shadow/20.png \
    image/shadow/21.png \
    image/shadow/22.png \
    image/shadow/23.png \
    image/shadow/3.png \
    image/shadow/4.png \
    image/shadow/5.png \
    image/shadow/6.png \
    image/shadow/7.png \
    image/shadow/8.png \
    image/shadow/9.png \
    savegame.txt \
    sound/backgrand.mp3 \
    sound/pair.wav \
    sound/pair.wav \
    sound/release.wav \
    sound/release.wav \
    sound/select.wav \
    sound/select.wav

RESOURCES += \
    icons.qrc
