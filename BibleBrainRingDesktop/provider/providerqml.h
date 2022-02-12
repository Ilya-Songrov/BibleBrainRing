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

#include "global_enums.h"

class ProviderQml : public QObject
{
    Q_OBJECT

    int currentAppState;
    int currentAppMode;

    Q_PROPERTY(int currentAppState READ getCurrentAppState WRITE setCurrentAppState NOTIFY currentAppStateChanged)
    Q_PROPERTY(int currentAppMode  READ getCurrentAppMode  WRITE setCurrentAppMode  NOTIFY currentAppModeChanged)
public:
    explicit ProviderQml(QObject *parent = nullptr);

    void setCurrentAppState(const BibleBrainRing::AppState appState);
    void setCurrentAppMode(const BibleBrainRing::AppMode appMode);

private:
    void setCurrentAppState(const int appState);
    void setCurrentAppMode(const int appMode);

    int getCurrentAppState();
    int getCurrentAppMode();

signals:
    void currentAppStateChanged();
    void currentAppModeChanged();

    void showMessage(const QString &message);

    void onEndQmlCreation();
    void onQmlButtonClicked(const BibleBrainRing::Button button);
};

