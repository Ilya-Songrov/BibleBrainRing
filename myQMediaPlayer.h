#ifndef MYQMEDIAPLAYER_H
#define MYQMEDIAPLAYER_H

#include "ui_mainwindow.h"

#include <QObject>
#include <QMediaPlayer>
#include <QSlider>
#include <QStyle>
#include <QTime>

class myQMediaPlayer : public QMediaPlayer
{
public:
    myQMediaPlayer(Ui::MainWindow *uiMain, QVector <QString> &vecStrMusicSector, QWidget *parent = 0);

    Ui::MainWindow *ui;

    bool currentSource;
    bool PlayingMusicTimer;
    bool SomeTrackStop;
    QString strMusicTimer;
    QVector <QString> &vecStrMusic;


    void setupSettingsWidets();
    void setupConnections();
    QString msecsToString(qint64 n);


    void music_startPause_clicked();
    void music_reset_clicked();
private slots:
    void slotSetMediaPosition (int n);
    void slotSetSliderPosition(qint64 n);
    void slotSetDuration(qint64 n);

public slots:
    void slotChangeStrMusicTimer(QString strMusicTimerPlayer){ strMusicTimer = strMusicTimerPlayer; }
};

#endif // MYQMEDIAPLAYER_H
