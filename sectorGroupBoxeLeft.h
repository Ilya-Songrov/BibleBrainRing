#ifndef SECTORGROUPBOXELEFT_H
#define SECTORGROUPBOXELEFT_H

#include "myQListWidget.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QDir>

class SectorGroupBoxeLeft : public QObject
{
    Q_OBJECT
public:
    SectorGroupBoxeLeft(Ui::MainWindow *uiMain, QVector <QString> &vecStrMusicSector);

private:
    Ui::MainWindow *ui;
    QVector <QString> &vecStrMusic;
    QMenu *contextMenuMp3;
    QString strMusicTimer;
    QPixmap pixMp3_Wav;
    QPixmap pixTimerMusic;

    void setupGroupBoxLeft_mp3();
    void setupActionsAndConnections();

private slots:
    void slotDropMp3(QString strPathDrop, QString objectNameN);
public slots:
    void slotActivatedMp3(QAction* pAction);
    void slotExecContextMenuMp3(const QPoint &);

signals:
    void signalChangeStrMusicTimerGroupBoxeLeft(QString strMusicTimer);
    void signalLoadMusicTrack();
};

#endif // SECTORGROUPBOXELEFT_H
