QT += core gui

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
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    .gitignore \
    image/background.jpg \
    image/board1.jpeg \
    image/board1_settings.jpg \
    image/board2.jpeg \
    image/board2_settings.jpg \
    image/board3.jpeg \
    image/board3_settings.jpg \
    image/board4.jpeg \
    image/board4_settings.jpg \
    image/board5.jpeg \
    image/board5_settings.jpg \
    image/board6.jpeg \
    image/board6_settings.jpg \
    image/board7.jpeg \
    image/board7_settings.jpg \
    image/board8.jpeg \
    image/board8_settings.jpg \
    image/board9.jpeg \
    image/board9_settings.jpg \
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
    image/tropy.jpg \
    image/tropy2.png \
    image/tropy2_cut.png \
    image/tropy3.png \

RESOURCES += \
    resource2.qrc
