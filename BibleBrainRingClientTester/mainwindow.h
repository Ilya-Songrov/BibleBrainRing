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

#include <QMainWindow>

#include "tcp/tcpclient.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void on_pushButton_GenerateClient_clicked();

    void on_pushButton_Disconnect_clicked();

    void on_pushButton_Connect_clicked();

    void on_pushButton_SendData_clicked();

private:
    TcpClient* findClient(const QString& clientLocalAddressPort);

private:
    Ui::MainWindow *ui;
    QList<TcpClient*> listTcpClients;
};
