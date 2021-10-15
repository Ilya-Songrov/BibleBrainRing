QT       += core gui
QT += network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    $$PWD/../BibleBrainRingServerLib/src/information/informationconsoleprinter.cpp \
    $$PWD/../BibleBrainRingServerLib/src/iodevice/tcp/readwritesocket.cpp \
    $$PWD/main.cpp \
    $$PWD/mainwindow.cpp \
    $$PWD/tcp/tcpclient.cpp

HEADERS += \
    $$PWD/../BibleBrainRingServerLib/include/biblebrainringserverlib/information/informationconsoleprinter.h \
    $$PWD/../BibleBrainRingServerLib/include/biblebrainringserverlib/iodevice/tcp/readwritesocket.h \
    $$PWD/mainwindow.h \
    $$PWD/tcp/tcpclient.h

FORMS += \
    mainwindow.ui

INCLUDEPATH += \
    $$PWD/../BibleBrainRingServerLib/include \
    $$PWD/../BibleBrainRingServerLib/include/biblebrainringserverlib/information \
    $$PWD/../BibleBrainRingServerLib/include/biblebrainringserverlib/iodevice/tcp \
    $$PWD/../BibleBrainRingServerLib/src/information \
    $$PWD/../BibleBrainRingServerLib/src/iodevice/tcp \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
