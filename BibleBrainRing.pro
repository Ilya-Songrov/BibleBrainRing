#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T20:04:55
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = BibleBrainRing
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    Core/MyQGraphicsTextItem.cpp \
    Core/MyQMediaPlayer.cpp \
    Core/QuestionSearch.cpp \
    Core/QuestionPreviewForm.cpp \
    Core/QDialogAdministration.cpp \
    Core/QDialogSettingsScreens.cpp \
    Core/SectorGraphicsView.cpp \
    Core/SectorGroupBoxLeft.cpp \
    Core/SectorGroupBoxRight.cpp \
    Core/SectorPlayerAndTimer.cpp \
    Core/SectorActions.cpp \
    Core/StructScreens.cpp


HEADERS  += mainwindow.h \
    Core/MyQListWidget.h \
    Core/MyComboBox.h \
    Core/MyProxyStyleHTMLdelegate.h \
    Core/MyQGraphicsTextItem.h \
    Core/MyQMediaPlayer.h \
    Core/QuestionSearch.h \
    Core/QuestionPreviewForm.h \
    Core/QDialogAdministration.h \
    Core/QDialogSettingsScreens.h \
    Core/SectorGraphicsView.h \
    Core/SectorGroupBoxLeft.h \
    Core/SectorGroupBoxRight.h \
    Core/SectorPlayerAndTimer.h \
    Core/SectorActions.h \
    Core/StructScreens.h

INCLUDEPATH += \
    Core

FORMS    += \
    mainwindow.ui \

#CONFIG = x86_64

RESOURCES += \
    resources_file1.qrc


RC_FILE = myapp.rc


DISTFILES += \
    myapp.rc



