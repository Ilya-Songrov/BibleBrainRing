/**************************************************************************
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU
** General Public License version 3 as published by the Free Software
** Foundation with exceptions as appearing in the file LICENSE.GPL3
** included in the packaging of this file. Please review the following
** information to ensure the GNU General Public License requirements will
** be met: https://www.gnu.org/licenses/.
**
**************************************************************************/

#include "InitStateMain.h"

InitStateMain::InitStateMain(QQmlApplicationEngine *qmlApplicationEngine, QObject *parent)
    : StateAbstract(__FUNCTION__, parent)
  , _qmlApplicationEngine(qmlApplicationEngine)
{
    providerQml->setCurrentAppState(BibleBrainRing::Init);
    listScreens->initScreens();
    setQmlSettings();
    loadQml();
}

StateAbstract *InitStateMain::onEndQmlCreation()
{
    return new StartStateMenuMain();
}

void InitStateMain::setQmlSettings()
{
    _qmlApplicationEngine->rootContext()->setContextProperty("providerQml", providerQml.get());
    _qmlApplicationEngine->rootContext()->setContextProperty("managerQuestionsQml", managerQuestions.get());
    qmlRegisterUncreatableMetaObject(
                BibleBrainRing::staticMetaObject,       // static meta object
                "biblebrainring.namespace",             // import statement (can be any string)
                1, 0,                                   // major and minor version of the import
                "BibleBrainRing",                       // name in QML (does not have to match C++ name)
                "Error: only enums"                     // error in case someone tries to create a MyNamespace object
                );
    qRegisterMetaType<BibleBrainRing::AppState>("BibleBrainRing::AppState"); // not qmlRegister but qRegister
    qRegisterMetaType<BibleBrainRing::Button>("BibleBrainRing::Button"); // not qmlRegister but qRegister
    qmlRegisterType<ListModel>("ListModelQml", 1, 0, "ListModel");
    qmlRegisterType<ListModelScreens>("ListModelScreensQml", 1, 0, "ListModelScreens");
    _qmlApplicationEngine->rootContext()->setContextProperty("listTeamsRegistrationQml", listTeamsRegistration.get());
    _qmlApplicationEngine->rootContext()->setContextProperty("listTeamsInGameSessionQml", listTeamsInGameSession.get());
    _qmlApplicationEngine->rootContext()->setContextProperty("listTeamsInBattleQml", listTeamsInBattle.get());
    _qmlApplicationEngine->rootContext()->setContextProperty("listTeamsInResultQml", listTeamsInResult.get());
    _qmlApplicationEngine->rootContext()->setContextProperty("listScreensQml", listScreens.get());
}

void InitStateMain::loadQml()
{
    QTimer::singleShot(0, this, [this](){
        _qmlApplicationEngine->load("qrc:/qmlFiles/qmlFiles/main.qml");
    });
}








