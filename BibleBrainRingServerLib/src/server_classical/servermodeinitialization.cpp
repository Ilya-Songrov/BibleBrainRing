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

#include "servermodeinitialization.h"

ServerModeInitialization::ServerModeInitialization(IODeviceServerAbstract *ioDeviceServerAbstract, QObject *parent) : ServerModeAbstract(ServerMode::Initialization, __FUNCTION__, parent)
{
    io = ioDeviceServerAbstract;
}

ServerModeAbstract *ServerModeInitialization::initServer()
{
    const bool ret = io->initServer();
    if (ret) {
        io->pauseAcceptingClients();
        return new ServerModeIdle();
    }
    return nullptr;
}

