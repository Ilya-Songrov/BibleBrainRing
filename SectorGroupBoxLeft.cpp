#include "SectorGroupBoxLeft.h"

SectorGroupBoxLeft::SectorGroupBoxLeft(Ui::MainWindow *uiMain, QVector <QString> &vecStrMusicSector) :
    ui(uiMain),
    vecStrMusic(vecStrMusicSector)
{
    setupGroupBoxLeft_mp3();
    setupActionsAndConnections();
}

void SectorGroupBoxLeft::setupGroupBoxLeft_mp3()
{
    // для музыки нужно еще добавлять (qrc) поскольку QUrl() не читает.
    vecStrMusic.push_back("qrc:/new/GroupBoxes/MaterialsGroupBoxes/SoundQuestion.mp3");
    vecStrMusic.push_back("qrc:/new/GroupBoxes/MaterialsGroupBoxes/SoundIncorrectAnswer.wav");
    vecStrMusic.push_back("qrc:/new/GroupBoxes/MaterialsGroupBoxes/SoundTimer.mp3");
    strMusicTimer = "qrc:/new/GroupBoxes/MaterialsGroupBoxes/SoundTimer.mp3";

    pixMp3_Wav = QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/IconMusic.png").scaled(QSize(35,35),
                                                                        Qt::IgnoreAspectRatio);
    pixTimerMusic = QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/IconTimer.png").
                                                scaled(QSize(35,35),Qt::IgnoreAspectRatio);

        QPalette pal = ui->listWidget_Music->palette();
        pal.setColor(QPalette::Text, QColor(206,190,255).darker(199));
        pal.setColor(QPalette::Active, QPalette::Base, QColor(216,244,255).lighter(81));
        pal.setColor(QPalette::Inactive, QPalette::Base, QColor(216,244,255).lighter(81));
        ui->listWidget_Music->setPalette(pal);

    ui->listWidget_Music->setIconSize(QSize(35, 35));

    QListWidgetItem* pitem = 0;

        pitem = new QListWidgetItem("Питання.mp3", ui->listWidget_Music);
            pitem->setIcon(pixMp3_Wav);

        pitem = new QListWidgetItem("Хибна відповідь.wav", ui->listWidget_Music);
            pitem->setIcon(pixMp3_Wav);

        pitem = new QListWidgetItem("Таймер.mp3", ui->listWidget_Music);
            pitem->setIcon(pixTimerMusic);

        ui->listWidget_Music->setCurrentItem(pitem);
}

void SectorGroupBoxLeft::setupActionsAndConnections()
{
    contextMenuMp3 = new QMenu(ui->menu);/* доделать в конце подыскать родителя*/
    contextMenuMp3->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Delete1.png"),"Видалити вибране");
    contextMenuMp3->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/DeleteAll.png"),"Видалити все окрім таймера");
    contextMenuMp3->addAction(QIcon(":/new/GroupBoxes/MaterialsGroupBoxes/IconTimer.png"),"Встановити музикою таймера");
    contextMenuMp3->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Load.png"),"Завантажити");
    connect(contextMenuMp3,SIGNAL(triggered(QAction*)),SLOT(slotActivatedMp3(QAction*)));
    connect(ui->listWidget_Music, &MyQListWidget::signalDropListWidgetMp3, this, &SectorGroupBoxLeft::slotDropMp3);


    connect(ui->listWidget_Music, &MyQListWidget::customContextMenuRequested, this,
            &SectorGroupBoxLeft::slotExecContextMenuMp3);
}

void SectorGroupBoxLeft::slotExecContextMenuMp3(const QPoint &)
{
    contextMenuMp3->exec(QCursor::pos());
}

void SectorGroupBoxLeft::slotActivatedMp3(QAction *pAction)
{
    if(pAction->text() == "Видалити вибране"){
        if(vecStrMusic.size() != 0 && vecStrMusic[ui->listWidget_Music->currentRow()] != strMusicTimer)
        {
            vecStrMusic.remove(ui->listWidget_Music->currentRow());
            QListWidgetItem *it = ui->listWidget_Music->item(ui->listWidget_Music->currentRow());
            delete it;
        }
    }
    if(pAction->text() == "Видалити все окрім таймера"){
        for (int var = 0; var < vecStrMusic.size(); ++var)
        {
                QListWidgetItem *it = ui->listWidget_Music->item(ui->listWidget_Music->currentRow());
                delete it;
        }
        vecStrMusic.clear();//Сначала все удаляется, после вставляется только муз.таймер
        vecStrMusic.push_back(strMusicTimer);
        QListWidgetItem* pitem = 0;
        pitem = new QListWidgetItem("Таймер", ui->listWidget_Music);
        pitem->setIcon(pixTimerMusic);
        ui->listWidget_Music->setCurrentItem(pitem);
    }
    if(pAction->text() == "Встановити музикою таймера"){
        if(vecStrMusic.size() != 0 && vecStrMusic[ui->listWidget_Music->currentRow()] != strMusicTimer)
        {
            for (int var = 0; var < vecStrMusic.size(); ++var)
                if(vecStrMusic[var] == strMusicTimer){
                    ui->listWidget_Music->item(var)->setIcon(pixMp3_Wav);
                }
// Сначала меняется предыдущая картинка таймера на pixMp3_Wav, после новый трек получает pixTimerMusic
            strMusicTimer = vecStrMusic[ui->listWidget_Music->currentRow()];
            emit signalChangeStrMusicTimerGroupBoxLeft(strMusicTimer);
            ui->listWidget_Music->item(ui->listWidget_Music->currentRow())->setIcon(pixTimerMusic);
        }

    }
    if(pAction->text() == "Завантажити"){
        emit signalLoadMusicTrack();
    }

}

void SectorGroupBoxLeft::slotDropMp3(QString strPathDrop, QString objectNameN)
{
    QStringList listDrop;
    listDrop = strPathDrop.split(QLatin1Char('\n'),QString :: SkipEmptyParts);

    if(objectNameN == "listWidget_Music")// Если это mp3 и listWidget котрый слева.
    {
        for (int var = 0; var < listDrop.size(); ++var)
        {
            vecStrMusic.push_back(listDrop[var]);
            QListWidgetItem* pitem = 0;
            pitem = new QListWidgetItem(QDir(listDrop[var]).dirName(), ui->listWidget_Music);
            pitem->setIcon(pixMp3_Wav);
        }
    }
}
