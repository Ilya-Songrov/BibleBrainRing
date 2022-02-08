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

#pragma once

#include <QObject>

namespace BibleBrainRing {

Q_NAMESPACE
enum AppState {
    None,
    Init,
    StartMenu,
    RunServer,
    Registration,
    GameSession,
    ShowResult,
};
Q_ENUM_NS(AppState)

enum Button {
    ButtonStartServerWifi,
    ButtonStartServerBluetooth,
    ButtonStartServerHttp,
    ButtonStartClientWifi,
    ButtonStartClientBluetooth,
    ButtonStartOnlyProgram,
};
Q_ENUM_NS(Button)

}
