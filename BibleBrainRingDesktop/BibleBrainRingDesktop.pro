include($$PWD/../BibleBrainRingServerLib/biblebrainringserverlib.pri)
include($$PWD/../Exceptions/exceptions.pri)

QT += quick
QT += widgets
QT += gui

TARGET = BibleBrainRing
CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


HEADERS += \
    BibleBrainRingApplicationEngine.h \
    global/global_enums.h \
    global/global_utils.h \
    information/InformationAbstract.h \
    information/InformationSettings.h \
    managers/ManagerQuestions/ManagerQuestions.hpp \
    managers/ManagerQuestions/QuestionsFileParser.hpp \
    managers/ManagerScreens/ManagerScreens.hpp \
    provider/ProviderQuestions.hpp \
    provider/ProviderScreens.hpp \
    provider/providerqml.h \
    state_machine/ShowingResult/ShowingResult.hpp \
    state_machine/StateAbstract.h \
    state_machine/all_states.h \
    state_machine/game_session/GameSession.hpp \
    state_machine/init/InitStateMain.h \
    state_machine/registration/RegistrationStateMain.h \
    state_machine/start_menu/StartStateMenuMain.h \
    view/AdditionalScreen.hpp \
    view/ListModel.hpp \
    view/ListModelScreens.hpp \
    view/ListScreens.hpp \
    view/ListTeams.hpp

SOURCES += \
    BibleBrainRingApplicationEngine.cpp \
    global/global_utils.cpp \
    information/InformationAbstract.cpp \
    information/InformationSettings.cpp \
    managers/ManagerQuestions/ManagerQuestions.cpp \
    managers/ManagerQuestions/QuestionsFileParser.cpp \
    managers/ManagerScreens/ManagerScreens.cpp \
    provider/ProviderQuestions.cpp \
    provider/ProviderScreens.cpp \
    provider/providerqml.cpp \
    state_machine/ShowingResult/ShowingResult.cpp \
    state_machine/StateAbstract.cpp \
    state_machine/game_session/GameSession.cpp \
    state_machine/init/InitStateMain.cpp \
    state_machine/registration/RegistrationStateMain.cpp \
    state_machine/start_menu/StartStateMenuMain.cpp \
    main.cpp \
    view/AdditionalScreen.cpp \
    view/ListModel.cpp \
    view/ListModelScreens.cpp \
    view/ListScreens.cpp \
    view/ListTeams.cpp

RESOURCES += \
    resources/qmlFiles.qrc \
    resources/visualData.qrc

INCLUDEPATH += \
    information \
    global \
    provider \
    view \
    managers/ManagerQuestions \
    managers/ManagerScreens \
    state_machine \
    state_machine/init \
    state_machine/start_menu \
    state_machine/registration \
    state_machine/game_session \
    state_machine/ShowingResult

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
