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

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->lineEdit_ServerAddressPort->setText("127.0.0.1:9090");
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_GenerateClient_clicked()
{
    TcpClient* client = new TcpClient(this);
    const QString addressPort = ui->lineEdit_ServerAddressPort->text();
    const auto list = addressPort.split(":");
    const bool ret = client->connectToServer(list.at(0), list.at(1).toUShort());
    if (ret) {
        listTcpClients.append(client);
        ui->comboBox->addItem(client->getLocalAddressPort());
        ui->comboBox->setCurrentIndex(ui->comboBox->count() - 1);
    }
}

void MainWindow::on_pushButton_Disconnect_clicked()
{
    auto* client = findClient(ui->comboBox->currentText());
    qWarning() << "write me" << client << __LINE__ << Qt::endl;
}


void MainWindow::on_pushButton_Connect_clicked()
{
    auto* client = findClient(ui->comboBox->currentText());
    qWarning() << "write me" << client << __LINE__ << Qt::endl;
}

void MainWindow::on_pushButton_SendData_clicked()
{
    auto* client = findClient(ui->comboBox->currentText());
    if (client) {
        const auto data = ui->textEdit_Data->toPlainText();
        qDebug() << "Send to server:" << data << Qt::endl;
        client->sendToServerParams(QJsonValue(data), "test");
    }
    else{
        qWarning() << "Error. Client is not exist" << Qt::endl;
    }
}

TcpClient *MainWindow::findClient(const QString &clientLocalAddressPort)
{
    const auto it = std::find_if(std::begin(listTcpClients), std::end(listTcpClients), [clientLocalAddressPort](const TcpClient* client){ return client->getLocalAddressPort() == clientLocalAddressPort;});
    return it != std::end(listTcpClients) ? *it : nullptr;
}

