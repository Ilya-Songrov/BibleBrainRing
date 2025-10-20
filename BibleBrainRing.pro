#-------------------------------------------------
#
# Project created by QtCreator 2017-03-27T20:04:55
#
#-------------------------------------------------

QT       += core gui
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = Bible' 'Brain' 'Ring
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    myQGraphicsTextItem.cpp \
    QuestionSearch.cpp \
    QuestionPreviewForm.cpp \
    QDialogAdministration.cpp \
    QDialogSettingsScreens.cpp \
    SectorGraphicsView.cpp \
    SectorGroupBoxeLeft.cpp \
    SectorGroupBoxeRight.cpp \
    myQMediaPlayer.cpp \
    SectorPlayerAndTimer.cpp \
    SectorActions.cpp \
    StructScreens.cpp


HEADERS  += mainwindow.h \
    myQListWidget.h \
    myQGraphicsTextItem.h \
    myComboBox.h \
    myProxyStyleHTMLdelegate.h \
    QuestionSearch.h \
    QuestionPreviewForm.h \
    QDialogAdministration.h \
    QDialogSettingsScreens.h \
    SectorGraphicsView.h \
    SectorGroupBoxeLeft.h \
    SectorGroupBoxeRight.h \
    myQMediaPlayer.h \
    SectorPlayerAndTimer.h \
    SectorActions.h \
    StructScreens.h



FORMS    += \
    mainwindow.ui \

#CONFIG = x86_64

RESOURCES += \
    resources_file1.qrc


RC_FILE = myapp.rc


DISTFILES += \
    myapp.rc



