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

    Q_PROPERTY(int currentAppState READ getCurrentAppState WRITE setCurrentAppState NOTIFY currentAppStateChanged)
public:
    explicit ProviderQml(QObject *parent = nullptr);

    void setCurrentAppState(const BibleBrainRing::AppState appState);

private:
    void setCurrentAppState(const int appState);

    int getCurrentAppState();

signals:
    void currentAppStateChanged();

    void showMessage(const QString &message);

    void onEndQmlCreation();
    void onQmlButtonClicked(const BibleBrainRing::Button button);
};

