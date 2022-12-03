QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Move.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    Move.h \
    mainwindow.h \
    utils.h

FORMS += \
    mainwindow.ui \
    mainwindow_old.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    image/background.jpg \
    image/black_piece.png \
    image/blue_king.png \
    image/blue_piece.png \
    image/board.jpeg \
    image/board2.png \
    image/board3.png \
    image/board4.png \
    image/board5.png \
    image/board6.png \
    image/board7.png \
    image/board8.png \
    image/board9.png \
    image/board_new.jpeg \
    image/celebrate.jpg \
    image/celebrate2.jpg \
    image/crumpled_paper.jpg \
    image/flag1.png \
    image/flag2.png \
    image/flag3.png \
    image/flag4.png \
    image/flag5.png \
    image/flag6.png \
    image/flag7.png \
    image/green_piece.png \
    image/navy_piece.png \
    image/orange_piece.png \
    image/red_piece.png \
    image/tropy.jpg \
    image/tropy2.png \
    image/tropy2_cut.png \
    image/tropy3.png \
    image/violet_piece.png \
    image/white_piece.png \
    image/yellow_king.png \
    image/yellow_piece.png

RESOURCES += \
    resource2.qrc
