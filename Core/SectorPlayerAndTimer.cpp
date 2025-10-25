#include "SectorPlayerAndTimer.h"

SectorPlayerAndTimer::SectorPlayerAndTimer(Ui::MainWindow *uiMain, QVector<QString> &vecStrMusicSector) :
    ui(uiMain),
    vecStrMusic(vecStrMusicSector),
    int_timer_basic(10),
    int_timer_speed(28)
{
    setupPlayer();
    setupTimer();
    setupConnections();
}

SectorPlayerAndTimer::~SectorPlayerAndTimer()
{
    delete MyMediaPlayer;
}

void SectorPlayerAndTimer::setupPlayer()
{    
    MyMediaPlayer = new MyQMediaPlayer(ui, vecStrMusic);
    connect(this, &SectorPlayerAndTimer::signalChangeStrMusicTimerPlayer, MyMediaPlayer,
                &MyQMediaPlayer::slotChangeStrMusicTimer);
}

void SectorPlayerAndTimer::setupTimer()
{
    timer.setInterval(20);
    connect(&timer, &QTimer::timeout, this, &SectorPlayerAndTimer::slotTimer);
}

void SectorPlayerAndTimer::setupConnections()
{
    connect(ui->listWidget_Music, &QListWidget::itemActivated, this,
            &SectorPlayerAndTimer::slotOnListWidget_Music_itemActivatedSector);
    connect(ui->pushButton_MusicStartPause, &QPushButton::clicked, this,
            &SectorPlayerAndTimer::slotOnPushButton_MusicStartPause_clickedSector);
    connect(ui->pushButton_MusicReset, &QPushButton::clicked, this,
            &SectorPlayerAndTimer::slotOnPushButton_MusicReset_clickedSector);
    connect(ui->pushButton_MusicOpen, &QPushButton::clicked, this,
            &SectorPlayerAndTimer::slotOnPushButton_MusicOpen_clickedSector);

    connect(ui->pushButton_timer_on_off, &QPushButton::clicked, this,
            &SectorPlayerAndTimer::slotOnPushButton_timer_on_off_clickedSector);
    connect(ui->pushButton_timer_reset, &QPushButton::clicked, this,
            &SectorPlayerAndTimer::slotOnPushButton_timer_reset_clickedSector);
}


void SectorPlayerAndTimer::slotTimer()
{
    QString strMinus = "   ";
    int mseconds = 0;

    if(boolComeback)// Якщо це повернення.
    {
        intComeback += 1000;
        mseconds = intComeback / 1000 * 1000;// Це для того щоб мілісекунди завжди були 3 нолики.

        if(intComeback >= int_timer_basic * 1000){// Якщо перевалили за точку відліку.
            emit signalWriteTextChanged_on_TimerItem(QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000)
                .second(), "   " + QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000).toString("mm:ss:zzz"));
            timer.stop();
            timer.setInterval(20);
            boolComeback = false;
            timePause = QTime::fromMSecsSinceStartOfDay(0);
            ui->pushButton_timer_on_off->setText("Увімк.");
            ui->pushButton_timer_on_off->setChecked(false);
            return;
        }
    }
    else// Якщо це звичайний рух таймера вниз.
    {
        mseconds = (int_timer_basic * 1000) - (timePause.msecsSinceStartOfDay() +
                    QTime::currentTime().msecsSinceStartOfDay() - timeLastStart.msecsSinceStartOfDay());
        intComeback = mseconds;// Записуємо скільки опустився таймер в мілісекундах, потім стільки ж піднімемося.
    }

    if(mseconds < 0){// Якщо число від'ємне ми його робимо додатним, оскільки QTime не розуміє мінус.
        mseconds = mseconds * -1;
        strMinus = " - ";
        if(!boolComeback){// Для того щоб секунду ноль не показувати 2 рази.
            mseconds += 1000;
        }
        QMenu *sceneMenu = ui->menuBar->findChild<QMenu *>("sceneMenu");
        QMenu *sceneMenuTimer = sceneMenu->findChild<QMenu *>("sceneMenuTimer");
        QAction *aTimerNegativeNumbers = sceneMenuTimer->findChild<QAction *>("aTimerNegativeNumbers");

            if(!aTimerNegativeNumbers->isChecked()){// Якщо не потрібно йти в мінус. Робимо паузу.
                slotOnPushButton_timer_on_off_clickedSector(!ui->pushButton_timer_on_off->isChecked());
                return;
        }
    }

    // якщо секунда від'ємна, відправляємо від'ємною.
    emit signalWriteTextChanged_on_TimerItem(strMinus != " - " ?
        QTime::fromMSecsSinceStartOfDay(mseconds).second() : QTime::fromMSecsSinceStartOfDay(mseconds).second() * -1,
                            strMinus + QTime::fromMSecsSinceStartOfDay(mseconds).toString("mm:ss:zzz"));
}


void SectorPlayerAndTimer::timer_on_off_clicked(bool checked)
{
    if(!checked)
    {
        timer.stop();
        timePause = QTime::fromMSecsSinceStartOfDay(timePause.msecsSinceStartOfDay() + QTime::currentTime().
                             msecsSinceStartOfDay() - timeLastStart.msecsSinceStartOfDay());
        ui->pushButton_timer_on_off->setChecked(false);
        ui->pushButton_timer_on_off->setText("Увімк.");
    }
    else
    {
        timeLastStart = QTime::currentTime();
        timer.start(20);
        boolComeback = false;// Якщо раптом повернення не закінчилося, а ми натиснули пуск, тут скасовується повернення.
        ui->pushButton_timer_on_off->setChecked(true);
        ui->pushButton_timer_on_off->setText("Вимк.");
    }
}


void SectorPlayerAndTimer::timer_reset_clicked()
{
    QMenu *sceneMenu = ui->menuBar->findChild<QMenu *>("sceneMenu");
    QMenu *sceneMenuTimer = sceneMenu->findChild<QMenu *>("sceneMenuTimer");
    QAction *aTimerComeback = sceneMenuTimer->findChild<QAction *>("aTimerComeback");

    if(aTimerComeback->isChecked() == true)
    {
        timer.stop();
        boolComeback = true;// Відмічаємо що почалося повернення.
        timer.start(int_timer_speed);// Уповільнюємо таймер для повернення.
        timePause = QTime::fromMSecsSinceStartOfDay(0);

        ui->pushButton_timer_on_off->setText("Увімк.");
        ui->pushButton_timer_on_off->setChecked(false);

    }
    else
    {
        emit signalWriteTextChanged_on_TimerItem(QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000).
                second(), "   " + QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000).toString("mm:ss:zzz"));
        timer.stop();
        timer.setInterval(20);
        boolComeback = false;
        timePause = QTime::fromMSecsSinceStartOfDay(0);
        ui->pushButton_timer_on_off->setText("Увімк.");
        ui->pushButton_timer_on_off->setChecked(false);
    }
}

void SectorPlayerAndTimer::slotOnPushButton_timer_on_off_clickedSector(bool checked)
{
    if(ui->checkBox_music_timer->isChecked() == true &&
            vecStrMusic[ui->listWidget_Music->currentRow()] == MyMediaPlayer->strMusicTimer
        && (MyMediaPlayer->PlayingMusicTimer == true || MyMediaPlayer->SomeTrackStop == true))
    { // якщо зв'язані музика і таймер і поточний трек (метрономний) на паузі
        MyMediaPlayer->music_startPause_clicked();
        timer_on_off_clicked(checked);
    }
    else if(ui->checkBox_music_timer->isChecked() == true &&
            MyMediaPlayer->PlayingMusicTimer == true)
    { // якщо зв'язані музика і таймер і поточний трек є метрономний
        MyMediaPlayer->music_startPause_clicked();
        timer_on_off_clicked(checked);
    }
    else
    {
        timer_on_off_clicked(checked);
    }
}

void SectorPlayerAndTimer::slotOnPushButton_timer_reset_clickedSector()
{
    if(ui->checkBox_music_timer->isChecked() == true &&
            vecStrMusic[ui->listWidget_Music->currentRow()] == MyMediaPlayer->strMusicTimer
            && (MyMediaPlayer->PlayingMusicTimer == true || MyMediaPlayer->SomeTrackStop == true))
    { // якщо зв'язані музика і таймер і поточний трек (метрономний) на паузі
        MyMediaPlayer->music_reset_clicked();
        timer_reset_clicked();
    }
    else if(ui->checkBox_music_timer->isChecked() == true &&
            MyMediaPlayer->PlayingMusicTimer == true)
    { // якщо зв'язані музика і таймер і поточний трек є метрономний
        MyMediaPlayer->music_reset_clicked();
        timer_reset_clicked();
    }
    else
    {
        timer_reset_clicked();
    }
}

void SectorPlayerAndTimer::slotOnListWidget_Music_itemActivatedSector(QListWidgetItem *item)
{
    if(ui->checkBox_music_timer->isChecked() == true &&
            vecStrMusic[ui->listWidget_Music->row(item)] == MyMediaPlayer->strMusicTimer)
    { // якщо зв'язані музика і таймер і поточний трек є метрономний

        MyMediaPlayer->music_reset_clicked();
        MyMediaPlayer->music_startPause_clicked();
        timer_reset_clicked();
        timer_on_off_clicked(true);
    }
    else
    {
        MyMediaPlayer->music_reset_clicked();
        MyMediaPlayer->music_startPause_clicked();
    }
}

void SectorPlayerAndTimer::slotOnPushButton_MusicStartPause_clickedSector()
{
    if(ui->checkBox_music_timer->isChecked() == true &&
            vecStrMusic[ui->listWidget_Music->currentRow()] == MyMediaPlayer->strMusicTimer
            && (MyMediaPlayer->PlayingMusicTimer == true || MyMediaPlayer->SomeTrackStop == true))
    { // якщо зв'язані музика і таймер і поточний трек (метрономний) на паузі
        MyMediaPlayer->music_startPause_clicked();
        timer_on_off_clicked(!ui->pushButton_timer_on_off->isChecked());
    }
    else if(ui->checkBox_music_timer->isChecked() == true &&
            MyMediaPlayer->PlayingMusicTimer == true)
    { // якщо зв'язані музика і таймер і поточний трек є метрономний
        MyMediaPlayer->music_startPause_clicked();
        timer_on_off_clicked(!ui->pushButton_timer_on_off->isChecked());
    }
    else
    {
        MyMediaPlayer->music_startPause_clicked();
    }
}

void SectorPlayerAndTimer::slotOnPushButton_MusicReset_clickedSector()
{
    if(ui->checkBox_music_timer->isChecked() == true &&
            vecStrMusic[ui->listWidget_Music->currentRow()] == MyMediaPlayer->strMusicTimer
        && (MyMediaPlayer->PlayingMusicTimer == true || MyMediaPlayer->SomeTrackStop == true))
    { // якщо зв'язані музика і таймер і поточний трек (метрономний) на паузі
        MyMediaPlayer->music_reset_clicked();
        timer_reset_clicked();
    }
    else if(ui->checkBox_music_timer->isChecked() == true && MyMediaPlayer->PlayingMusicTimer == true)
    { // якщо зв'язані музика і таймер і поточний трек є метрономний
        MyMediaPlayer->music_reset_clicked();
        timer_reset_clicked();
    }
    else
    {
        MyMediaPlayer->music_reset_clicked();
    }
}

void SectorPlayerAndTimer::slotOnPushButton_MusicOpen_clickedSector()
{
    QString strFilter;
    QString str = QFileDialog::getOpenFileName(0,tr("Open Music"), QDir::currentPath(),
            "Music (*.mp3 *.wav)", &strFilter);

    if (!str.isEmpty())
    {
        qDebug() << "function: " << __FUNCTION__ << " str: " << str << Qt::endl;
        qDebug() << "function: " << __FUNCTION__ << " QUrl::fromLocalFile(str).toLocalFile(): " << QUrl::fromLocalFile(str).toLocalFile() << Qt::endl;
        vecStrMusic.push_back("file://" + QUrl::fromLocalFile(str).toLocalFile());

        QListWidgetItem* pitem = 0;
        pitem = new QListWidgetItem(QFileInfo(str).fileName(), ui->listWidget_Music);
        pitem->setIcon(QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/IconMusic.png").scaled(QSize(35,35),
                                                                        Qt::IgnoreAspectRatio));

    }
}

void SectorPlayerAndTimer::slotOnActionSceneMenu_timer_time_triggeredSector()
{
    QDialog dialog;
    dialog.setWindowFlags(Qt::WindowCloseButtonHint);
    QSpinBox *spinBox = new QSpinBox(&dialog);
    spinBox->setMinimumHeight(45);
    spinBox->setValue(int_timer_basic);

    QPushButton *pushButton1 = new QPushButton(&dialog);
    pushButton1->setText("Ok");
    QPushButton *pushButton2 = new QPushButton(&dialog);
    pushButton2->setText("Cancel");
    QGridLayout gridLayout;
    gridLayout.addWidget(spinBox,0,0,1,0);
    gridLayout.addWidget(pushButton1,1,0);
    gridLayout.addWidget(pushButton2,1,1);
    dialog.setLayout(&gridLayout);

    dialog.setFixedSize(dialog.minimumSize());
    connect(pushButton1,SIGNAL(clicked()),&dialog,SLOT(accept()));
    connect(pushButton2,SIGNAL(clicked()),&dialog,SLOT(reject()));
    if(dialog.exec() == QDialog::Accepted)
    {
        int_timer_basic = spinBox->value();
        // оновлюємо відображення таймера з новим часом
        emit signalWriteTextChanged_on_TimerItem(QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000).
                second(), "   " + QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000).toString("mm:ss:zzz"));
        // повідомляємо про зміну базового значення таймера
        emit signalTimerBasicValueChanged(int_timer_basic);
    }
}

void SectorPlayerAndTimer::slotOnActionSceneMenu_timer_speed_triggeredSector()
{
    QDialog dialog;
    dialog.setWindowFlags(Qt::WindowCloseButtonHint);

    QLabel *label = new QLabel(&dialog);
    label->setText("50    = 50-millisecond timer \n"
                   "1000  = 1-second timer \n"
                   "60000 = 1-minute timer \n");
    QSpinBox *spinBox = new QSpinBox(&dialog);
    spinBox->setMinimumHeight(45);
    spinBox->setMaximum(100000);
    spinBox->setValue(int_timer_speed);
    QPushButton *pushButton1 = new QPushButton(&dialog);
    pushButton1->setText("Ok");
    QPushButton *pushButton2 = new QPushButton(&dialog);
    pushButton2->setText("Cancel");
    QGridLayout gridLayout;
    gridLayout.addWidget(label,0,0,1,0);
    gridLayout.addWidget(spinBox,1,0,1,0);
    gridLayout.addWidget(pushButton1,2,0);
    gridLayout.addWidget(pushButton2,2,1);
    dialog.setLayout(&gridLayout);

    dialog.setFixedSize(dialog.minimumSize());
    connect(pushButton1,SIGNAL(clicked()),&dialog,SLOT(accept()));
    connect(pushButton2,SIGNAL(clicked()),&dialog,SLOT(reject()));
    if(dialog.exec() == QDialog::Accepted)
    {
        int_timer_speed = spinBox->value();
    }
}
