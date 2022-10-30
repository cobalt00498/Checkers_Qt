QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Board.cpp \
    HumanPlayer.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Board.h \
    HumanPlayer.h \
    Player.h \
    mainwindow.h \
    utils.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    image/background.jpg \
    image/blue_heart.png \
    image/blue_piece.png \
    image/board.jpeg \
    image/orange_heart.png \
    image/red_heart.png \
    image/yellow_heart.png \
    image/yellow_piece.png

RESOURCES += \
    resource2.qrc
