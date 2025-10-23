#ifndef SECTORPLAYERANDTIMER_H
#define SECTORPLAYERANDTIMER_H

#include "ui_mainwindow.h"
#include "MyQMediaPlayer.h"

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

    MyQMediaPlayer *MyMediaPlayer;
    QTimer timer; // Викликає сигнал і відкату і звичайного руху таймера.
    QTime timePause;
    QTime timeLastStart;
    bool boolComeback = false;
    int int_timer_basic;
    int intComeback; // За цим числом зручно відкочувати таймер.
    // дорівнює 10. Будемо помножувати на 1000(переводячи в мілісекунди), щоб не було проблем якщо введуть 67 секунд.
    int int_timer_speed; // швидкість відкату

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
    void signalTimerBasicValueChanged(int newTimerBasic); // сигнал про зміну базового значення таймера
};

#endif // SECTORPLAYERANDTIMER_H
