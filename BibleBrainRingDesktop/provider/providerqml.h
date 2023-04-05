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
    bool visibleBulbOnScreen;
    bool useReferee;
    QString currentHttpServerHostPort;
    QString textResult;

    Q_PROPERTY(int currentAppState                  READ getCurrentAppState             WRITE setCurrentAppState            NOTIFY currentAppStateChanged)
    Q_PROPERTY(int currentAppMode                   READ getCurrentAppMode              WRITE setCurrentAppMode             NOTIFY currentAppModeChanged)
    Q_PROPERTY(int visibleBulbOnScreen              READ getVisibleBulbOnScreen         WRITE setVisibleBulbOnScreen        NOTIFY visibleBulbOnScreenChanged)
    Q_PROPERTY(int useReferee                       READ getUseReferee                  WRITE setUseReferee                 NOTIFY useRefereeChanged)
    Q_PROPERTY(QString currentHttpServerHostPort    READ getCurrentHttpServerHostPort   WRITE setCurrentHttpServerHostPort  NOTIFY currentHttpServerHostPortChanged)
    Q_PROPERTY(QString textResult                   READ getTextResult                  WRITE setTextResult                 NOTIFY textResultChanged)
public:
    explicit ProviderQml(QObject *parent = nullptr);

    void setCurrentAppState(const BibleBrainRing::AppState appState);
    void setCurrentAppMode(const BibleBrainRing::AppMode appMode);
    void setVisibleBulbOnScreen(const bool value);
    void setUseReferee(const bool value);
    void setCurrentHttpServerHostPort(const QString& hostPort);
    void setTextResult(const QString& value);

    bool getUseReferee();
    QString getTextResult();

private:
    void setCurrentAppState(const int appState);
    void setCurrentAppMode(const int appMode);

    int getCurrentAppState();
    int getCurrentAppMode();
    bool getVisibleBulbOnScreen();
    QString getCurrentHttpServerHostPort();

signals:
    void currentAppStateChanged();
    void currentAppModeChanged();
    void visibleBulbOnScreenChanged();
    void useRefereeChanged();
    void currentHttpServerHostPortChanged();
    void textResultChanged();

    void showMessage(const QString &message);

    void onEndQmlCreation();
    void onQmlButtonClicked(const BibleBrainRing::Button button);
    void resetBulbScore(const qint64 time);
};

