#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTime"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_settings("Ilya","BrainRing"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Структура для хранения информации об экранах. Собственном и если подключен проэктор, тогда и о нем.
    structScreens.setParentWidget(this);
    structScreens.initializationDesktop();

    // Здесь обрабатывается информация QActions которые находятся в меню. Конечно есть и исключение.
    sectorActions = new SectorActions(ui, structScreens, m_settings);

    // Здесь обрабатываем все что касается бокса справа.
    sectorGroupBoxeRight = new SectorGroupBoxeRight(ui);

    // Здесь обрабатываем все что касается бокса слева.
    sectorGroupBoxeLeft = new SectorGroupBoxeLeft(ui, vecStrMusic);

    // Этот класс занимается музыкой и таймером. Все расчеты здесь.
    sectorPlayerAndTimer = new SectorPlayerAndTimer(ui, vecStrMusic);

    // Этот класс самый большой. Он занят графическим интерфейсом. Как все будет выглядеть в приложении и на
    // экране решается здесь. Также возможности редактирования осуществленны в этом классе.
    sectorGraphicsView = new SectorGraphicsView(ui, sectorPlayerAndTimer->getInt_timer_basic(), structScreens,
                                                m_settings);
    // Класс для работы с вопросами. Загрузка,разшифровка, поиск.
    questionSearch = new QuestionSearch(ui, this);


    setupFront(); // Настройки касаемо всего приложения.
    setupConnections(); // Установка связей между классами, а также видлжетами и их слотами.
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sectorActions;
    delete sectorGroupBoxeRight;
    delete sectorGroupBoxeLeft;
    delete sectorPlayerAndTimer;
    delete sectorGraphicsView;
    delete questionSearch;
    if(m_settings.value("boolClearRestore", false).toBool()){
        m_settings.clear(); // если настройки сброшены, мы очищаем.
        m_settings.setValue("boolClearRestore", false);
    }
    /* доделать в конце удалить классы в динамической памяти*/
}

void MainWindow::setupConnections()
{
// Связи между классами
    connect(sectorActions, &SectorActions::signalQuestionFastLoad,
                questionSearch, &QuestionSearch::questionFastLoad);
    connect(sectorGroupBoxeLeft, &SectorGroupBoxeLeft::signalChangeStrMusicTimerGroupBoxeLeft,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::signalChangeStrMusicTimerPlayer);
    connect(sectorGroupBoxeLeft, &SectorGroupBoxeLeft::signalLoadMusicTrack,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::slotOnPushButton_MusicOpen_clickedSector);
    connect(sectorGroupBoxeRight, &SectorGroupBoxeRight::signalSetBackgroundBrush,
                sectorGraphicsView, &SectorGraphicsView::slotSetBackgroundBrush);
    connect(sectorPlayerAndTimer, &SectorPlayerAndTimer::signalWriteTextChanged_on_TimerItem,
                sectorGraphicsView, &SectorGraphicsView::slotWriteTextChanged_on_TimerItem);
    connect(sectorGraphicsView, &SectorGraphicsView::aTimeToActionSceneMenuTimerTimeTriggered,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::slotOnActionSceneMenu_timer_time_triggeredSector);
    connect(sectorGraphicsView, &SectorGraphicsView::aSpeedToActionSceneMenuTimerSpeedTriggered,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::slotOnActionSceneMenu_timer_speed_triggeredSector);
    connect(questionSearch, &QuestionSearch::signalShowQuestion,
                sectorGraphicsView, &SectorGraphicsView::slotQuestionPublic);


// связи для QAction
    connect(ui->action_question_fast, &QAction::triggered, this, [&]() {questionSearch->questionFastLoad(false);});
    connect(ui->action_question_decocer, &QAction::triggered, this,
                                             [&]() {questionSearch->showPreviewFormDecoder(QDir::currentPath());});
    connect(ui->action_save, &QAction::triggered, sectorActions, &SectorActions::slotOnAction_save_triggeredSector);
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->action_Screens, &QAction::triggered, sectorGraphicsView, &SectorGraphicsView::slotSettingsScreens);
    connect(ui->action_Restore_by_default, &QAction::triggered, this, [&]{
                    m_settings.setValue("boolClearRestore", true);
                    QMessageBox::information(this,"Title","Настройки сбросятся со следующего запуска. \n"
                                              "Можете перезагрузить приложение.");});
    connect(ui->action_administration, &QAction::triggered, sectorActions,
                            &SectorActions::slotOnAction_administration_triggered);
    connect(ui->action_Opening_questions_help, &QAction::triggered, sectorActions,
            &SectorActions::slotOnAction_Opening_questions_help_triggered);
    connect(ui->action_Screens_help, &QAction::triggered, sectorActions,
            &SectorActions::slotOnAction_Screens_help_triggered);
    connect(ui->action_developer, &QAction::triggered, sectorActions,
            &SectorActions::slotOnAction_developer_triggered);
    connect(ui->action_AboutQt, &QAction::triggered, sectorActions,
                                            &SectorActions::slotOnAction_AboutQt_triggered);
    connect(ui->action_ItemLoadPixmap, &QAction::triggered, sectorGraphicsView,
                                            &SectorGraphicsView::slotSetLoadPixmap);
    connect(ui->action_ItemPixmapSize, &QAction::triggered, sectorGraphicsView,
            &SectorGraphicsView::slotSetItemPixmapSize);

// связи остальные
    connect(ui->pushButton_color, &QPushButton::clicked, sectorGraphicsView,
            &SectorGraphicsView::slotOnPushButton_color_clicked);
        QShortcut * shortCutTimer = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_D), this);
    connect(shortCutTimer, &QShortcut::activated, ui->pushButton_timer_on_off, &QPushButton::click);
}

void MainWindow::setupFront()
{
    this->setWindowIconText("Bible' 'Brain' 'Ring");
    this->setWindowTitle("Bible Brain Ring");
        QPalette pal_Window; // фон всего приложения
        pal_Window.setBrush(QPalette::Background,QBrush(Qt::lightGray));
        setPalette(pal_Window);
    ui->mainToolBar->setVisible(false);


    // Устанавливаем это, чтобы поисковые слова были выделенны желтым цветом.
    ui->comboBox_question->setStyle(new myProxyStyle);
    ui->comboBox_question->setItemDelegate(new myStyledItemDelegate);
}

void MainWindow::keyPressEvent(QKeyEvent *pe)
{
    switch (pe->key())
    {
        case Qt::Key_Escape:
            sectorActions->slotOn_pushButton_hide_clicked();
        break;
        default:
        QWidget::keyPressEvent(pe); // Передать событие дальше
    }
}
