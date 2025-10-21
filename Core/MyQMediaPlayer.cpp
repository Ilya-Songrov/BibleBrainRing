#include "MyQMediaPlayer.h"

MyQMediaPlayer::MyQMediaPlayer(Ui::MainWindow *uiMain,  QVector <QString> &vecStrMusicSector, QWidget *parent)  :
    QMediaPlayer(parent),
    ui(uiMain),
    currentSource(true), //поточний трек змінюється залежно від значення цієї змінної
    PlayingMusicTimer(false), //доки "звучить" музика таймера змінна == true
    SomeTrackStop(true),//означає що будь-який трек знаходиться в зупиненому стані
    strMusicTimer("qrc:/new/GroupBoxes/MaterialsGroupBoxes/SoundTimer.mp3"),
    vecStrMusic(vecStrMusicSector)
{
    setVolume(50);
    setupSettingsWidets();
    setupConnections();
}

void MyQMediaPlayer::setupSettingsWidets()
{
    ui->pushButton_MusicStartPause->setIcon(QMainWindow().style()->standardIcon(QStyle::SP_MediaPlay));
    ui->pushButton_MusicReset->setIcon(QMainWindow().style()->standardIcon(QStyle::SP_MediaStop));
    ui->label_Music_Current->setText(msecsToString(0));
    ui->label_Music_Remain->setText(msecsToString(0));
    ui->verticalSlider_volume->setRange(0, 100);
    ui->verticalSlider_volume->setValue(50);
}

void MyQMediaPlayer::setupConnections()
{
    connect(ui->verticalSlider_volume, SIGNAL(valueChanged(int)), this, SLOT(setVolume(int)));
    connect(ui->horizontalSlider_music, &QSlider::sliderMoved, this, &MyQMediaPlayer::slotSetMediaPosition);
    connect(this, &QMediaPlayer::positionChanged, this, &MyQMediaPlayer::slotSetSliderPosition);
    connect(this, &QMediaPlayer::durationChanged, this, &MyQMediaPlayer::slotSetDuration);
}

QString MyQMediaPlayer::msecsToString(qint64 n)
{
    int nHours   = (n / (60 * 60 * 1000));
    int nMinutes = ((n  % (60 * 60 * 1000)) / (60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);

    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

void MyQMediaPlayer::music_startPause_clicked()
{
        if (currentSource == true)
        {
            setMedia(QUrl(vecStrMusic[ui->listWidget_Music->currentRow()]));
            currentSource = false;
            if(vecStrMusic[ui->listWidget_Music->currentRow()] == strMusicTimer){
                PlayingMusicTimer = true;
            }
            SomeTrackStop = false;
        }

    switch(this->state())
    {
    case MyQMediaPlayer::PlayingState:
        this->pause();
        ui->pushButton_MusicStartPause->setText("Пуск");
        ui->pushButton_MusicStartPause->setIcon(QMainWindow().style()->standardIcon(QStyle::SP_MediaPlay));
        break;
    default:
        this->play();
        ui->pushButton_MusicStartPause->setText("Пауза");
        ui->pushButton_MusicStartPause->setIcon(QMainWindow().style()->standardIcon(QStyle::SP_MediaPause));
        break;
    }
}

void MyQMediaPlayer::music_reset_clicked()
{
    this->stop();
    ui->pushButton_MusicStartPause->setText("Пуск");
    ui->pushButton_MusicStartPause->setIcon(QMainWindow().style()->standardIcon(QStyle::SP_MediaPlay));
    currentSource = true;
    PlayingMusicTimer = false;
    SomeTrackStop = true;
}

void MyQMediaPlayer::slotSetMediaPosition(int n)
{
    this->setPosition(n);
}

void MyQMediaPlayer::slotSetSliderPosition(qint64 n)
{
    ui->horizontalSlider_music->setValue(n);

    int nDuration = ui->horizontalSlider_music->maximum();
    ui->label_Music_Current->setText(msecsToString(n));
    ui->label_Music_Remain->setText(msecsToString(nDuration - n));
}

void MyQMediaPlayer::slotSetDuration(qint64 n)
{
    ui->horizontalSlider_music->setRange(0, n);
    ui->label_Music_Current->setText(msecsToString(0));
    ui->label_Music_Remain->setText(msecsToString(n));
}
