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

#include "providerqml.h"

ProviderQml::ProviderQml(QObject *parent) : QObject(parent)
  , currentAppState(BibleBrainRing::None)
  , currentAppMode(BibleBrainRing::AppModeNone)
{

}

void ProviderQml::setCurrentAppState(const BibleBrainRing::AppState appState)
{
    setCurrentAppState((int)appState);
}

void ProviderQml::setCurrentAppMode(const BibleBrainRing::AppMode appMode)
{
    setCurrentAppMode((int)appMode);
}

void ProviderQml::setCurrentAppState(const int appState)
{
    currentAppState = appState;
    emit currentAppStateChanged();
}

void ProviderQml::setCurrentAppMode(const int appMode)
{
    currentAppMode = appMode;
    emit currentAppModeChanged();
}

int ProviderQml::getCurrentAppState()
{
    return currentAppState;
}

int ProviderQml::getCurrentAppMode()
{
    return currentAppMode;
}
