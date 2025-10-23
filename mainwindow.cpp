#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QTime"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_settings("BibleBrainRingOrganization", "BibleBrainRingApplication"),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Структура для зберігання інформації про екрани. Власний і якщо підключено проектор, тоді і про нього.
    structScreens.setParentWidget(this);
    structScreens.initializationDesktop();

    // Тут обробляється інформація QActions які знаходяться в меню. Звичайно є і виняток.
    sectorActions = new SectorActions(ui, structScreens, m_settings);

    // Тут обробляємо все що стосується бокса справа.
    sectorGroupBoxRight = new SectorGroupBoxRight(ui);

    // Тут обробляємо все що стосується бокса зліва.
    sectorGroupBoxLeft = new SectorGroupBoxLeft(ui, vecStrMusic);

    // Цей клас займається музикою і таймером. Всі розрахунки тут.
    sectorPlayerAndTimer = new SectorPlayerAndTimer(ui, vecStrMusic);

    // Цей клас найбільший. Він зайнятий графічним інтерфейсом. Як все буде виглядати в додатку і на
    // екрані вирішується тут. Також можливості редагування здійснені в цьому класі.
    sectorGraphicsView = new SectorGraphicsView(ui, sectorPlayerAndTimer->getInt_timer_basic(), structScreens,
                                                m_settings);
    // Клас для роботи з питаннями. Завантаження, розшифровка, пошук.
    questionSearch = new QuestionSearch(ui, this);


    setupFront(); // Налаштування стосовно всього додатку.
    setupConnections(); // Встановлення зв'язків між класами, а також віджетами і їх слотами.
}

MainWindow::~MainWindow()
{
    delete ui;
    delete sectorActions;
    delete sectorGroupBoxRight;
    delete sectorGroupBoxLeft;
    delete sectorPlayerAndTimer;
    delete sectorGraphicsView;
    delete questionSearch;
    if(m_settings.value("boolClearRestore", false).toBool()){
        m_settings.clear(); // якщо налаштування скинуті, ми очищаємо.
        m_settings.setValue("boolClearRestore", false);
    }
    /* доробити в кінці видалити класи в динамічній пам'яті*/
}

void MainWindow::setupConnections()
{
// Зв'язки між класами
    connect(sectorActions, &SectorActions::signalQuestionFastLoad, this, [&](bool boolQuestionsonEsther) {
        questionSearch->questionFastLoad(boolQuestionsonEsther);
        // зберігаємо шлях до файла після завантаження (тільки якщо це не ресурсний файл)
        if (!boolQuestionsonEsther)
            sectorGraphicsView->setQuestionFilePath(questionSearch->getLastUsedQuestionFilePath());
    });
    connect(sectorGroupBoxLeft, &SectorGroupBoxLeft::signalChangeStrMusicTimerGroupBoxLeft,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::signalChangeStrMusicTimerPlayer);
    connect(sectorGroupBoxLeft, &SectorGroupBoxLeft::signalLoadMusicTrack,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::slotOnPushButton_MusicOpen_clickedSector);
    connect(sectorGroupBoxRight, &SectorGroupBoxRight::signalSetBackgroundBrush,
                sectorGraphicsView, &SectorGraphicsView::slotSetBackgroundBrush);
    connect(sectorPlayerAndTimer, &SectorPlayerAndTimer::signalWriteTextChanged_on_TimerItem,
                sectorGraphicsView, &SectorGraphicsView::slotWriteTextChanged_on_TimerItem);
    connect(sectorGraphicsView, &SectorGraphicsView::aTimeToActionSceneMenuTimerTimeTriggered,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::slotOnActionSceneMenu_timer_time_triggeredSector);
    connect(sectorGraphicsView, &SectorGraphicsView::aSpeedToActionSceneMenuTimerSpeedTriggered,
                sectorPlayerAndTimer, &SectorPlayerAndTimer::slotOnActionSceneMenu_timer_speed_triggeredSector);
    connect(questionSearch, &QuestionSearch::signalShowQuestion,
                sectorGraphicsView, &SectorGraphicsView::slotQuestionPublic);
    // підключаємо сигнал про стан завантаження питань
    connect(questionSearch, &QuestionSearch::questionsLoaded,
                sectorGraphicsView, &SectorGraphicsView::updateQuestionDisplayText);

    // синхронізація шляху до файла з питаннями між SectorGraphicsView та QuestionSearch
    // АВТОЗАВАНТАЖЕННЯ ПИТАНЬ:
    // 1. При запуску додатку завантажуємо збережений шлях до файла з питаннями
    // 2. Якщо файл існує, автоматично завантажуємо питання з нього
    // 3. При завантаженні нових питань через меню, шлях автоматично зберігається
    // 4. При закритті додатку всі налаштування, включаючи шлях до файла, зберігаються
    questionSearch->setLastUsedQuestionFilePath(sectorGraphicsView->getQuestionFilePath());
    // автоматично завантажуємо питання якщо є збережений шлях
    questionSearch->autoLoadQuestions();
    // перевіряємо початковий стан та оновлюємо відображення
    sectorGraphicsView->updateQuestionDisplayText(questionSearch->hasQuestions());


// зв'язки для QAction
    connect(ui->action_question_fast, &QAction::triggered, this, [&]() {
        questionSearch->questionFastLoad(false);
        // зберігаємо шлях до файла після завантаження
        sectorGraphicsView->setQuestionFilePath(questionSearch->getLastUsedQuestionFilePath());
    });
    connect(ui->action_question_decocer, &QAction::triggered, this, [&]() {
        questionSearch->showPreviewFormDecoder(QDir::currentPath());
        // зберігаємо шлях до файла після завантаження
        sectorGraphicsView->setQuestionFilePath(questionSearch->getLastUsedQuestionFilePath());
    });
    connect(ui->action_save, &QAction::triggered, sectorActions, &SectorActions::slotOnAction_save_triggeredSector);
    connect(ui->action_exit, &QAction::triggered, this, &MainWindow::close);
    connect(ui->action_Screens, &QAction::triggered, sectorGraphicsView, &SectorGraphicsView::slotSettingsScreens);
    connect(ui->action_Restore_by_default, &QAction::triggered, this, [&]{
                    m_settings.setValue("boolClearRestore", true);
        QMessageBox::information(this, "Title", "Налаштування скинуться з наступного запуску.\n"
                                                "Можете перезавантажити додаток.");
                    });
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

// зв'язки інші
    connect(ui->pushButton_color, &QPushButton::clicked, sectorGraphicsView,
            &SectorGraphicsView::slotOnPushButton_color_clicked);
        QShortcut * shortCutTimer = new QShortcut(QKeySequence(Qt::ALT + Qt::Key_D), this);
    connect(shortCutTimer, &QShortcut::activated, ui->pushButton_timer_on_off, &QPushButton::click);
}

void MainWindow::setupFront()
{
    this->setWindowIconText("BibleBrainRing");
    this->setWindowTitle("BibleBrainRing");
        QPalette pal_Window; // фон всього додатку
        pal_Window.setBrush(QPalette::Background,QBrush(Qt::lightGray));
        setPalette(pal_Window);
    ui->mainToolBar->setVisible(false);


    // Встановлюємо це, щоб пошукові слова були виділені жовтим кольором.
    ui->comboBox_question->setStyle(new MyProxyStyle);
    ui->comboBox_question->setItemDelegate(new MyStyledItemDelegate);
}

void MainWindow::keyPressEvent(QKeyEvent *pe)
{
    switch (pe->key())
    {
        case Qt::Key_Escape:
            sectorActions->slotOn_pushButton_hide_clicked();
        break;
        default:
        QWidget::keyPressEvent(pe); // Передати подію далі
    }
}
