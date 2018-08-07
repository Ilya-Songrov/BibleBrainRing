#include "SectorGroupBoxeLeft.h"

SectorGroupBoxeLeft::SectorGroupBoxeLeft(Ui::MainWindow *uiMain, QVector <QString> &vecStrMusicSector) :
    ui(uiMain),
    vecStrMusic(vecStrMusicSector)
{
    setupGroupBoxLeft_mp3();
    setupActionsAndConnections();
}

void SectorGroupBoxeLeft::setupGroupBoxLeft_mp3()
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

        pitem = new QListWidgetItem("Вопрос", ui->listWidget_Music);
            pitem->setIcon(pixMp3_Wav);

        pitem = new QListWidgetItem("Не правильный ответ.wav", ui->listWidget_Music);
            pitem->setIcon(pixMp3_Wav);

        pitem = new QListWidgetItem("Таймер", ui->listWidget_Music);
            pitem->setIcon(pixTimerMusic);

        ui->listWidget_Music->setCurrentItem(pitem);
}

void SectorGroupBoxeLeft::setupActionsAndConnections()
{
    contextMenuMp3 = new QMenu(ui->menu);/* доделать в конце подыскать родителя*/
    contextMenuMp3->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Delete1.png"),"Удалить");
    contextMenuMp3->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/DeleteAll.png"),"Удалить почти все");
    contextMenuMp3->addAction(QIcon(":/new/GroupBoxes/MaterialsGroupBoxes/IconTimer.png"),"Музыка таймера");
    contextMenuMp3->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Load.png"),"Загрузить");
    connect(contextMenuMp3,SIGNAL(triggered(QAction*)),SLOT(slotActivatedMp3(QAction*)));
    connect(ui->listWidget_Music, &myQListWidget::signalDropListWidgetMp3, this, &SectorGroupBoxeLeft::slotDropMp3);


    connect(ui->listWidget_Music, &myQListWidget::customContextMenuRequested, this,
            &SectorGroupBoxeLeft::slotExecContextMenuMp3);
}

void SectorGroupBoxeLeft::slotExecContextMenuMp3(const QPoint &)
{
    contextMenuMp3->exec(QCursor::pos());
}

void SectorGroupBoxeLeft::slotActivatedMp3(QAction *pAction)
{
    if(pAction->text() == "Удалить"){
        if(vecStrMusic.size() != 0 && vecStrMusic[ui->listWidget_Music->currentRow()] != strMusicTimer)
        {
            vecStrMusic.remove(ui->listWidget_Music->currentRow());
            QListWidgetItem *it = ui->listWidget_Music->item(ui->listWidget_Music->currentRow());
            delete it;
        }
    }
    if(pAction->text() == "Удалить почти все"){
        for (int var = 0; var < vecStrMusic.size(); ++var)
        {
                QListWidgetItem *it = ui->listWidget_Music->item(ui->listWidget_Music->currentRow());
                delete it;
        }
        vecStrMusic.clear();//Сначала все удаляется, после вставляется только муз.таймер

        vecStrMusic.push_back(strMusicTimer);
        QListWidgetItem* pitem = 0;
        pitem = new QListWidgetItem(QDir(vecStrMusic[0]).dirName(), ui->listWidget_Music);
        pitem->setIcon(pixTimerMusic);
        ui->listWidget_Music->setCurrentItem(pitem);
    }
    if(pAction->text() == "Музыка таймера"){
        if(vecStrMusic.size() != 0 && vecStrMusic[ui->listWidget_Music->currentRow()] != strMusicTimer)
        {
            for (int var = 0; var < vecStrMusic.size(); ++var)
                if(vecStrMusic[var] == strMusicTimer){
                    ui->listWidget_Music->item(var)->setIcon(pixMp3_Wav);
                }
// Сначала меняется предыдущая картинка таймера на pixMp3_Wav, после новый трек получает pixTimerMusic
            strMusicTimer = vecStrMusic[ui->listWidget_Music->currentRow()];
            emit signalChangeStrMusicTimerGroupBoxeLeft(strMusicTimer);
            ui->listWidget_Music->item(ui->listWidget_Music->currentRow())->setIcon(pixTimerMusic);
        }

    }
    if(pAction->text() == "Загрузить"){
        emit signalLoadMusicTrack();
    }

}

void SectorGroupBoxeLeft::slotDropMp3(QString strPathDrop, QString objectNameN)
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
