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

#include "servermodeidle.h"

ServerModeIdle::ServerModeIdle(QObject *parent) : ServerModeAbstract(ServerMode::Idle, __FUNCTION__, parent)
{

}

ServerModeAbstract *ServerModeIdle::startRegistration()
{
    io->startAcceptingClients();
    return new ServerModeAcceptsRegistrations();
}

