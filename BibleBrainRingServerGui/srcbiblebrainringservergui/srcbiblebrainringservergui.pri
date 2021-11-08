HEADERS += \
    $$PWD/global/global_enums.h \
    $$PWD/global/global_utils.h \
    $$PWD/information/informationabstract.h \
    $$PWD/information/informationsettings.h \
    $$PWD/provider/providerqml.h \
    $$PWD/state_machine/all_states.h \
    $$PWD/state_machine/init/initstatemain.h \
    $$PWD/state_machine/registration/registrationstatemain.h \
    $$PWD/state_machine/start/startstatemain.h \
    $$PWD/state_machine/stateabstract.h

SOURCES += \
    $$PWD/global/global_utils.cpp \
    $$PWD/information/informationabstract.cpp \
    $$PWD/information/informationsettings.cpp \
    $$PWD/provider/providerqml.cpp \
    $$PWD/state_machine/init/initstatemain.cpp \
    $$PWD/state_machine/registration/registrationstatemain.cpp \
    $$PWD/state_machine/start/startstatemain.cpp \
    $$PWD/state_machine/stateabstract.cpp


RESOURCES += \
    $$PWD/resources/qmlFiles.qrc

INCLUDEPATH += \
    $$PWD/information \
    $$PWD/global \
    $$PWD/provider \
    $$PWD/state_machine \
    $$PWD/state_machine/init \
    $$PWD/state_machine/start \
    $$PWD/state_machine/registration \
    $$PWD/state_machine/gameSession
