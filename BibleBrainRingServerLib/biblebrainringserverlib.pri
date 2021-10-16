SOURCES += \
    $$PWD/src/biblebrainringserver.cpp \
    $$PWD/src/data/questions.cpp \
    $$PWD/src/data/standings.cpp \
    $$PWD/src/dtos/dtocreator.cpp \
    $$PWD/src/information/informationconsoleprinter.cpp \
    $$PWD/src/iodevice/iodeviceserverabstract.cpp \
    $$PWD/src/iodevice/tcp/readwritesocket.cpp \
    $$PWD/src/iodevice/tcp/tcpserver.cpp \
    $$PWD/src/server_classical/biblebrainringserverclassical.cpp \
    $$PWD/src/server_classical/servermodeabstract.cpp \
    $$PWD/src/server_classical/servermodeacceptsregistrations.cpp \
    $$PWD/src/server_classical/servermodegameabstract.cpp \
    $$PWD/src/server_classical/servermodeidle.cpp \
    $$PWD/src/server_classical/servermodeinitialization.cpp \
    $$PWD/src/server_classical/servermoderunningsparring.cpp \
    $$PWD/src/server_classical/servermodeselectingsparringteams.cpp \
    $$PWD/src/server_classical/servermodeshowinggameresult.cpp \
    $$PWD/src/server_classical/servermodeshowingsparringresult.cpp

HEADERS += \
    $$PWD/include/biblebrainringserverlib/biblebrainringserver_global.h \
    $$PWD/include/biblebrainringserverlib/biblebrainringserver.h \
    $$PWD/include/biblebrainringserverlib/data/questions.h \
    $$PWD/include/biblebrainringserverlib/data/standings.h \
    $$PWD/include/biblebrainringserverlib/dtos/answeraccepteddto.h \
    $$PWD/include/biblebrainringserverlib/dtos/dtoabstract.h \
    $$PWD/include/biblebrainringserverlib/dtos/dtocreator.h \
    $$PWD/include/biblebrainringserverlib/dtos/gamestatusdto.h \
    $$PWD/include/biblebrainringserverlib/dtos/sendanswerdto.h \
    $$PWD/include/biblebrainringserverlib/dtos/serverstatusdto.h \
    $$PWD/include/biblebrainringserverlib/dtos/teamdto.h \
    $$PWD/include/biblebrainringserverlib/dtos/teamregistrationdto.h \
    $$PWD/include/biblebrainringserverlib/enums/global_enums.h \
    $$PWD/include/biblebrainringserverlib/information/informationconsoleprinter.h \
    $$PWD/include/biblebrainringserverlib/iodevice/iodeviceserverabstract.h \
    $$PWD/include/biblebrainringserverlib/iodevice/tcp/readwritesocket.h \
    $$PWD/include/biblebrainringserverlib/iodevice/tcp/tcpserver.h \
    $$PWD/include/biblebrainringserverlib/server_classical/all_server_modes.h \
    $$PWD/include/biblebrainringserverlib/server_classical/biblebrainringserverclassical.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeabstract.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeacceptsregistrations.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodegameabstract.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeidle.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeinitialization.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermoderunningsparring.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeselectingsparringteams.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeshowinggameresult.h \
    $$PWD/include/biblebrainringserverlib/server_classical/servermodeshowingsparringresult.h

INCLUDEPATH += \
    $$PWD/include
