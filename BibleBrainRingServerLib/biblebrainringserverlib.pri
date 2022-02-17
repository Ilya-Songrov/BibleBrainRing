include($$PWD/../QtWebApp/QtWebApp/httpserver/httpserver.pri)
include($$PWD/../QtWebApp/QtWebApp/logging/logging.pri)
include($$PWD/../QtWebApp/QtWebApp/templateengine/templateengine.pri)

SOURCES += \
    $$PWD/src/biblebrainringserver.cpp \
    $$PWD/src/data/questions.cpp \
    $$PWD/src/data/standings.cpp \
    $$PWD/src/dtos/dtocreator.cpp \
    $$PWD/src/information/informationconsoleprinter.cpp \
    $$PWD/src/iodevice/bluetooth/BluetoothServer.cpp \
    $$PWD/src/iodevice/http/HttpServer.cpp \
    $$PWD/src/iodevice/http/MyRequestHandler.cpp \
    $$PWD/src/iodevice/iodeviceserverabstract.cpp \
    $$PWD/src/iodevice/none/NoneServer.cpp \
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
    $$PWD/src/server_classical/servermodeshowingsparringresult.cpp \
    $$PWD/src/utils/FileWorker.cpp

HEADERS += \
    $$PWD/src/biblebrainringserver_global.h \
    $$PWD/src/biblebrainringserver.h \
    $$PWD/src/data/questions.h \
    $$PWD/src/data/standings.h \
    $$PWD/src/dtos/AllDtos.hpp \
    $$PWD/src/dtos/DtoTeamActivationForBattleClientRs.hpp \
    $$PWD/src/dtos/DtoTeamActivationForBattleServerRq.hpp \
    $$PWD/src/dtos/DtoTeamRegistrationClientRq.h \
    $$PWD/src/dtos/DtoTeamRegistrationServerRs.h \
    $$PWD/src/dtos/answeraccepteddto.h \
    $$PWD/src/dtos/dtoabstract.h \
    $$PWD/src/dtos/dtocreator.h \
    $$PWD/src/dtos/gamestatusdto.h \
    $$PWD/src/dtos/sendanswerdto.h \
    $$PWD/src/dtos/serverstatusdto.h \
    $$PWD/src/dtos/teamdto.h \
    $$PWD/src/enums/global_enums.h \
    $$PWD/src/information/informationconsoleprinter.h \
    $$PWD/src/iodevice/bluetooth/BluetoothServer.hpp \
    $$PWD/src/iodevice/http/HttpServer.hpp \
    $$PWD/src/iodevice/http/MyRequestHandler.hpp \
    $$PWD/src/iodevice/iodeviceserverabstract.h \
    $$PWD/src/iodevice/none/NoneServer.h \
    $$PWD/src/iodevice/tcp/readwritesocket.h \
    $$PWD/src/iodevice/tcp/tcpserver.h \
    $$PWD/src/server_classical/all_server_modes.h \
    $$PWD/src/server_classical/biblebrainringserverclassical.h \
    $$PWD/src/server_classical/servermodeabstract.h \
    $$PWD/src/server_classical/servermodeacceptsregistrations.h \
    $$PWD/src/server_classical/servermodegameabstract.h \
    $$PWD/src/server_classical/servermodeidle.h \
    $$PWD/src/server_classical/servermodeinitialization.h \
    $$PWD/src/server_classical/servermoderunningsparring.h \
    $$PWD/src/server_classical/servermodeselectingsparringteams.h \
    $$PWD/src/server_classical/servermodeshowinggameresult.h \
    $$PWD/src/server_classical/servermodeshowingsparringresult.h \
    $$PWD/src/utils/FileWorker.hpp

INCLUDEPATH += \
    $$PWD/src
