#ifndef SECTORPLAYERANDTIMER_H
#define SECTORPLAYERANDTIMER_H

#include "ui_mainwindow.h"
#include "myQMediaPlayer.h"

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QFileDialog>
#include <QDir>
#include <QSpinBox>
#include <QListWidget>

class SectorPlayerAndTimer : public QObject
{
    Q_OBJECT
public:
    explicit SectorPlayerAndTimer(Ui::MainWindow *uiMain,  QVector <QString> &vecStrMusicSector);
    ~ SectorPlayerAndTimer();

private:
    Ui::MainWindow *ui;
    QVector <QString> &vecStrMusic;

    myQMediaPlayer *myMediaPlayer;
    QTimer timer; // Вызывает сигнал и отката и обычного движения таймера.
    QTime timePause;
    QTime timeLastStart;
    bool boolComeback = false;
    int int_timer_basic;
    int intComeback; // По этому числу удобно откатывать таймер.
    // равно 10. Будем умножать на 1000(переводя в миллисекунды), чтобы не было проблем если введут 67 секунд.
    int int_timer_speed; // скорость отката

    void setupPlayer();
    void setupTimer();
    void setupConnections();

public:
    int getInt_timer_basic(){ return int_timer_basic; }
private slots:
    void slotTimer();
    void timer_on_off_clicked(bool checked);
    void timer_reset_clicked();

public slots:
    void slotOnPushButton_timer_on_off_clickedSector(bool checked);
    void slotOnPushButton_timer_reset_clickedSector();
    void slotOnListWidget_Music_itemActivatedSector(QListWidgetItem *item);
    void slotOnPushButton_MusicStartPause_clickedSector();
    void slotOnPushButton_MusicReset_clickedSector();
    void slotOnPushButton_MusicOpen_clickedSector();
    void slotOnActionSceneMenu_timer_time_triggeredSector();
    void slotOnActionSceneMenu_timer_speed_triggeredSector();

signals:
    void signalWriteTextChanged_on_TimerItem(int int_SecondsTimer_changing_now, QString strTimer);
    void signalChangeStrMusicTimerPlayer(QString strMusicTimerPlayer);
};

#endif // SECTORPLAYERANDTIMER_H
