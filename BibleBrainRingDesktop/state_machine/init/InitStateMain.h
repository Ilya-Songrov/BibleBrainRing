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

#include <QQmlContext>
#include <QQmlApplicationEngine>
#include <QTimer>

#include "StateAbstract.h"
#include "all_states.h"
#include "InformationSettings.h"
#include "ListModel.hpp"

class InitStateMain : public StateAbstract
{
    QQmlApplicationEngine *_qmlApplicationEngine;
public:
    explicit InitStateMain(QQmlApplicationEngine *qmlApplicationEngine, QObject *parent = nullptr);

    virtual StateAbstract *onEndQmlCreation     () override;

private:
    void setQmlSettings();
    void loadQml();
};

