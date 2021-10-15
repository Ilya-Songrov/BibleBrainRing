SOURCES += \
    $$PWD/src/biblebrainringserver.cpp \
    $$PWD/src/data/questions.cpp \
    $$PWD/src/dtos/dtocreator.cpp \
    $$PWD/src/information/informationconsoleprinter.cpp \
    $$PWD/src/iodevice/iodeviceserverabstract.cpp \
    $$PWD/src/iodevice/tcp/readwritesocket.cpp \
    $$PWD/src/iodevice/tcp/tcpserver.cpp \
    $$PWD/src/server_classical/biblebrainringserverclassical.cpp \
    $$PWD/src/server_classical/servermodeabstract.cpp \
    $$PWD/src/server_classical/servermodeacceptsregistrations.cpp \
    $$PWD/src/server_classical/servermodeidle.cpp \
    $$PWD/src/server_classical/servermodeinitialization.cpp \
    $$PWD/src/server_classical/servermoderunninggamesession.cpp

HEADERS += \
    $$PWD/include/biblebrainringserver/biblebrainringserver_global.h \
    $$PWD/include/biblebrainringserver/biblebrainringserver.h \
    $$PWD/include/biblebrainringserver/data/questions.h \
    $$PWD/include/biblebrainringserver/dtos/answeraccepteddto.h \
    $$PWD/include/biblebrainringserver/dtos/dtoabstract.h \
    $$PWD/include/biblebrainringserver/dtos/dtocreator.h \
    $$PWD/include/biblebrainringserver/dtos/gamestatusdto.h \
    $$PWD/include/biblebrainringserver/dtos/sendanswerdto.h \
    $$PWD/include/biblebrainringserver/dtos/serverstatusdto.h \
    $$PWD/include/biblebrainringserver/dtos/teamdto.h \
    $$PWD/include/biblebrainringserver/dtos/teamregistrationdto.h \
    $$PWD/include/biblebrainringserver/enums/global_enums.h \
    $$PWD/include/biblebrainringserver/information/informationconsoleprinter.h \
    $$PWD/include/biblebrainringserver/iodevice/iodeviceserverabstract.h \
    $$PWD/include/biblebrainringserver/iodevice/tcp/readwritesocket.h \
    $$PWD/include/biblebrainringserver/iodevice/tcp/tcpserver.h \
    $$PWD/include/biblebrainringserver/server_classical/all_server_modes.h \
    $$PWD/include/biblebrainringserver/server_classical/biblebrainringserverclassical.h \
    $$PWD/include/biblebrainringserver/server_classical/servermodeabstract.h \
    $$PWD/include/biblebrainringserver/server_classical/servermodeacceptsregistrations.h \
    $$PWD/include/biblebrainringserver/server_classical/servermodeidle.h \
    $$PWD/include/biblebrainringserver/server_classical/servermodeinitialization.h \
    $$PWD/include/biblebrainringserver/server_classical/servermoderunninggamesession.h

INCLUDEPATH += \
    $$PWD/include/biblebrainringserver
