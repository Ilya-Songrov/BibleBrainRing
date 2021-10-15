include($$PWD/../../BibleBrainRingServerLib/biblebrainringserverlib.pri)
include($$PWD/../Exceptions/exceptions.pri)
include($$PWD/src.pri)

QT += quick
QT += widgets
QT += gui

TARGET = BibleBrainRing
CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += \
        biblebrainringapplicationengine.h

SOURCES += \
        biblebrainringapplicationengine.cpp \
        main.cpp


# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


#### cqtdeployer ####
CONFIG(release, debug | release) {
QMAKE_POST_LINK=/bin/bash -c \"cqtdeployer -bin $${OUT_PWD}/$${TARGET} -targetDir cqtdeploy-of-$${TARGET} -qmake $${QMAKE_QMAKE} -libDir $${PWD} \
                               -recursiveDepth 10 -qmlDir $${PWD} force-clear ; \"
}
#### cqtdeployer ####
