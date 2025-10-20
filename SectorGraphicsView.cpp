#include "SectorGraphicsView.h"

SectorGraphicsView::SectorGraphicsView(Ui::MainWindow *uiMain, int timerBasic, StructScreens &structScreens_,
                                       QSettings &m_settings_) :
    ui(uiMain),
    int_timer_basic(timerBasic),
    structScreens(structScreens_),
    m_settings(m_settings_)
{
    readSettingsSectorGraphicsView();
    setupEverythingThatAreAboveStage();
    setupAndCreateMainScene();
    setupAndCreateSceneSecond();

    setupPushButton_color();
}

SectorGraphicsView::~SectorGraphicsView()
{
//    delete sceneMenu; // удалять не нужно
    writeSettingsSectorGraphicsView();
    delete sceneMenuAllitem;
    delete sceneMenuTimer;
    delete sceneMenuUseItem;
}

void SectorGraphicsView::readSettingsSectorGraphicsView()
{
    // для сброса дефолта шрифта. По сути есть HTML, но чтобы лагов не было оставляем еще и дефолт шрифт.
    boolFontDefaultItemsReset = m_settings.value("boolFontReset", true).toBool();

m_settings.beginGroup("/SettingsN");

int Ncolor_for_DialogR = m_settings.value("/color_backgroundScene_DialogR", 85).toInt();
int Ncolor_for_DialogG = m_settings.value("/color_backgroundScene_DialogG", 255).toInt();
int Ncolor_for_DialogB = m_settings.value("/color_backgroundScene_DialogB", 127).toInt();
    color_backgroundScene_Dialog.setRgb(Ncolor_for_DialogR,Ncolor_for_DialogG,Ncolor_for_DialogB);

int NColorR0 = m_settings.value("/colorItem_LineTitleR", QColor(Qt::black).red()).toInt();
int NColorG0 = m_settings.value("/colorItem_LineTitleG", QColor(Qt::black).green()).toInt();
int NColorB0 = m_settings.value("/colorItem_LineTitleB", QColor(Qt::black).blue()).toInt();
    colorItem_LineTitle = QColor(NColorR0,NColorG0,NColorB0);
    strItem_LineTitle = m_settings.value("/strItem_LineTitle", strItem_LineTitle).toString();

int NColorR1 = m_settings.value("/colorItem_LineFirstTeamR", QColor(Qt::black).red()).toInt();
int NColorG1 = m_settings.value("/colorItem_LineFirstTeamG", QColor(Qt::black).green()).toInt();
int NColorB1 = m_settings.value("/colorItem_LineFirstTeamB", QColor(Qt::black).blue()).toInt();
    colorItem_LineFirstTeam = QColor(NColorR1,NColorG1,NColorB1);
    strItem_LineFirstTeam = m_settings.value("/strItem_LineFirstTeam",
                                                      strItem_LineFirstTeam).toString();

int NColorR2 = m_settings.value("/colorItem_LineSecondTeamR", QColor(Qt::black).red()).toInt();
int NColorG2 = m_settings.value("/colorItem_LineSecondTeamG", QColor(Qt::black).green()).toInt();
int NColorB2 = m_settings.value("/colorItem_LineSecondTeamB", QColor(Qt::black).blue()).toInt();
    colorItem_LineSecondTeam = QColor(NColorR2,NColorG2,NColorB2);
    strItem_LineSecondTeam = m_settings.value("/strItem_LineSecondTeam",
                                                       strItem_LineSecondTeam).toString();

int NColorR3 = m_settings.value("/colorItem_LineFirstPointsR", QColor(Qt::black).red()).toInt();
int NColorG3 = m_settings.value("/colorItem_LineFirstPointsG", QColor(Qt::black).green()).toInt();
int NColorB3 = m_settings.value("/colorItem_LineFirstPointsB", QColor(Qt::black).blue()).toInt();
    colorItem_LineFirstPoints = QColor(NColorR3,NColorG3,NColorB3);
    strItem_LineFirstPoints = m_settings.value("/strItem_LineFirstPoints",
                                                       strItem_LineFirstPoints).toString();

int NColorR4 = m_settings.value("/colorItem_LineSecondPointsR", QColor(Qt::black).red()).toInt();
int NColorG4 = m_settings.value("/colorItem_LineSecondPointsG", QColor(Qt::black).green()).toInt();
int NColorB4 = m_settings.value("/colorItem_LineSecondPointsB", QColor(Qt::black).blue()).toInt();
    colorItem_LineSecondPoints = QColor(NColorR4,NColorG4,NColorB4);
    strItem_LineSecondPoints = m_settings.value("/strItem_LineSecondPoints",
                                                       strItem_LineSecondPoints).toString();

int NQuestionR = m_settings.value("/colorItem_LineQuestionR", QColor(Qt::red).red()).toInt();
int NQuestionG = m_settings.value("/colorItem_LineQuestionG", QColor(Qt::red).green()).toInt();
int NQuestionB = m_settings.value("/colorItem_LineQuestionB", QColor(Qt::red).blue()).toInt();
    colorItem_LineQuestion = QColor(NQuestionR,NQuestionG,NQuestionB);

int NColorR5 = m_settings.value("/colorItem_LineTimerR", QColor(Qt::black).red()).toInt();
int NColorG5 = m_settings.value("/colorItem_LineTimerG", QColor(Qt::black).green()).toInt();
int NColorB5 = m_settings.value("/colorItem_LineTimerB", QColor(Qt::black).blue()).toInt();
    colorItem_LineTimer = QColor(NColorR5,NColorG5,NColorB5);


m_settings.endGroup();
}

void SectorGraphicsView::writeSettingsSectorGraphicsView()
{
    m_settings.setValue("boolFontReset", false);// Записываем ложь, чтобы потом не начинать с дефолта шрифта.

m_settings.beginGroup("/SettingsN");

    m_settings.setValue("/color_backgroundScene_DialogR", color_backgroundScene_Dialog.red());
    m_settings.setValue("/color_backgroundScene_DialogG", color_backgroundScene_Dialog.green());
    m_settings.setValue("/color_backgroundScene_DialogB", color_backgroundScene_Dialog.blue());

    m_settings.setValue("/colorItem_LineTitleR", Item_LineTitleText->defaultTextColor().red());
    m_settings.setValue("/colorItem_LineTitleG", Item_LineTitleText->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineTitleB", Item_LineTitleText->defaultTextColor().blue());
        m_settings.setValue("/strItem_LineTitle", Doc_LineTitleText->toHtml());

    m_settings.setValue("/colorItem_LineFirstTeamR", Item_LineFirstTeam->defaultTextColor().red());
    m_settings.setValue("/colorItem_LineFirstTeamG", Item_LineFirstTeam->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineFirstTeamB", Item_LineFirstTeam->defaultTextColor().blue());
        m_settings.setValue("/strItem_LineFirstTeam", Doc_LineFirstTeam->toHtml());

    m_settings.setValue("/colorItem_LineSecondTeamR", Item_LineSecondTeam->defaultTextColor().red());
    m_settings.setValue("/colorItem_LineSecondTeamG", Item_LineSecondTeam->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineSecondTeamB", Item_LineSecondTeam->defaultTextColor().blue());
        m_settings.setValue("/strItem_LineSecondTeam", Doc_LineSecondTeam->toHtml());

    m_settings.setValue("/colorItem_LineFirstPointsR", Item_LineFirstPoints->defaultTextColor().red());
    m_settings.setValue("/colorItem_LineFirstPointsG", Item_LineFirstPoints->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineFirstPointsB", Item_LineFirstPoints->defaultTextColor().blue());
        m_settings.setValue("/strItem_LineFirstPoints", Doc_LineFirstPoints->toHtml());

    m_settings.setValue("/colorItem_LineSecondPointsR", Item_LineSecondPoints->defaultTextColor().red());
    m_settings.setValue("/colorItem_LineSecondPointsG", Item_LineSecondPoints->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineSecondPointsB", Item_LineSecondPoints->defaultTextColor().blue());
        m_settings.setValue("/strItem_LineSecondPoints", Doc_LineSecondPoints->toHtml());

    m_settings.setValue("/colorItem_LineQuestionR", Item_LineQuestion->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineQuestionG", Item_LineQuestion->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineQuestionB", Item_LineQuestion->defaultTextColor().blue());

    m_settings.setValue("/colorItem_LineTimerR", Item_LineTimer->defaultTextColor().red());
    m_settings.setValue("/colorItem_LineTimerG", Item_LineTimer->defaultTextColor().green());
    m_settings.setValue("/colorItem_LineTimerB", Item_LineTimer->defaultTextColor().blue());

m_settings.endGroup();
}

void SectorGraphicsView::setupEverythingThatAreAboveStage()
{
    ui->toolButton_Bold_2->setIcon(QPixmap().fromImage(QImage(":/new/ActionImage/ActionImageScene/Bold.png")));
    ui->toolButton_Bold_2->setShortcut(QKeySequence::Bold);
    ui->toolButton_Italic_2->setIcon(QIcon(":/new/ActionImage/ActionImageScene/Italic.png"));
    ui->toolButton_Italic_2->setShortcut(QKeySequence::Italic);
    ui->toolButton_Underline_2->setIcon(QIcon(":/new/ActionImage/ActionImageScene/Underline.png"));
    ui->toolButton_Underline_2->setShortcut(QKeySequence::Underline);
    ui->toolButton_font_2->setIcon(QIcon(":/new/ActionImage/ActionImageScene/font_увеличить.png"));
    ui->toolButton_font_2->setIconSize(QSize(ui->toolButton_font_2->iconSize().width()+10
                                           ,ui->toolButton_font_2->iconSize().height()+10));

    ui->toolButton_color_2->setPopupMode(QToolButton::MenuButtonPopup);
    ui->toolButton_color_2->setMenu(createColorMenu(Qt::red));
    ui->toolButton_color_2->setIcon(QIcon(createColorToolButtonIcon(Qt::red)));
    ui->toolButton_color_2->setIconSize(QSize(ui->toolButton_color_2->iconSize().width()+5
                                        ,ui->toolButton_color_2->iconSize().height()+5));
    ui->toolButton_color_2->setAutoFillBackground(true);
    ui->toolButton_color_2->setPalette(QPalette(Qt::lightGray));

    ui->toolButton_plus_2->setIcon(QIcon(":/new/ActionImage/ActionImageScene/plus.png"));
    ui->toolButton_minus_2->setIcon(QIcon(":/new/ActionImage/ActionImageScene/minus.png"));


    // highlighted connect, и возможно второй, не должны использоваться так как они используются.
    // Дело в том что когда они подают сигнал слот редактирует текст. И если востользоваться Cntrl+Z
    // возрат будет происходить по пути изменения. Этот сигнал должен использовать для демонстрации
    // изменения текста, но не изменять, а уже когда пользователь нажал мышкой тогда уже редактировать ткст.
            connect(ui->fontSizeCombo_2,SIGNAL(highlighted(int)),this,SLOT
                    (slot_fontSizeCombo_highlighted_AND_activated(int)));
            connect(ui->fontSizeCombo_2,SIGNAL(activated(int)),this,SLOT
                    (slot_fontSizeCombo_highlighted_AND_activated(int)));
            connect(ui->toolButton_font_2, &QToolButton::clicked,this, &SectorGraphicsView::slotSetFont);

connect(ui->toolButton_plus_2, &QToolButton::clicked, this,
                                                &SectorGraphicsView::slotOnToolButton_plus_2_clicked);
connect(ui->toolButton_minus_2, &QToolButton::clicked, this,
                                                &SectorGraphicsView::slotOnToolButton_minus_2_clicked);
connect(ui->toolButton_Bold_2, &QToolButton::clicked, this,
                                                &SectorGraphicsView::slotOnToolButton_Bold_2_clicked);
connect(ui->toolButton_Italic_2, &QToolButton::clicked, this,
                                                &SectorGraphicsView::slotOnToolButton_Italic_2_clicked);
connect(ui->toolButton_Underline_2, &QToolButton::clicked, this,
                                                &SectorGraphicsView::slotOnToolButton_Underline_2_clicked);
connect(ui->toolButton_color_2, &QToolButton::clicked, this,
                                                &SectorGraphicsView::slotOnToolButton_color_2_clicked);

//--------------------------------------------------------------------------------------------------------
    sceneMenu = new QMenu(ui->menuBar);
    sceneMenu->setObjectName("sceneMenu");
    sceneMenu->setStyleSheet("color: black");
       sceneMenuAllitem = new QMenu("Всі надписи", sceneMenu);
            sceneMenuAllitem->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Text.png"));
            aFontAllitem = new QAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Font.png"),tr("Шрифт"), sceneMenuAllitem);
            aFontAllitem->setShortcut(Qt::CTRL + Qt::Key_F);
//                QShortcut* fontShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_F), sceneMenuAllitem);
//                connect(fontShortcut, &QShortcut::activated, aFontAllitem, &QAction::trigger);
            sceneMenuAllitem->addAction(aFontAllitem);
            aColorAllitem = new QAction(QIcon(":/new/ActionImage/ActionImageScene/colors.png"),tr("Колір"), sceneMenuAllitem);
            aColorAllitem->setShortcut(Qt::CTRL + Qt::Key_G);
            sceneMenuAllitem->addAction(aColorAllitem);
            aBackgroundAllitem = new QAction(tr("Колір Фона"), sceneMenuAllitem);
            aBackgroundAllitem->setShortcut(Qt::CTRL + Qt::Key_H);
            sceneMenuAllitem->addAction(aBackgroundAllitem);
            aRectAllitem = new QAction(tr("Описувати квадрати"), sceneMenuAllitem);
            aRectAllitem->setCheckable(true);
            aRectAllitem->setChecked(true);
            aAutoFontQuestion = new QAction(tr("Автоматичний шрифт питання"), sceneMenuAllitem);// Используется как флаг
            aAutoFontQuestion->setCheckable(true);
            aAutoFontQuestion->setChecked(true);
            aAutoZeroPoints = new QAction(tr("Обнуляти бали"), sceneMenuAllitem);// Используется как флаг
            aAutoZeroPoints->setCheckable(true);
            aAutoZeroPoints->setChecked(true);

        sceneMenuUseItem = new QMenu(sceneMenu);
        sceneMenuUseItem->setTitle("Використовувати елементи");
            aRemuveTitlePixmapItem = new QAction(tr("Заголовок зображення"), sceneMenuUseItem);
            aRemuveTitlePixmapItem->setCheckable(true);
            aRemuveTitlePixmapItem->setChecked(false);
            sceneMenuUseItem->addAction(aRemuveTitlePixmapItem);
            aRemuveTitleTextItem = new QAction(tr("Заголовок текст"), sceneMenuUseItem);
            aRemuveTitleTextItem->setCheckable(true);
            aRemuveTitleTextItem->setChecked(true);
            sceneMenuUseItem->addAction(aRemuveTitleTextItem);
            aRemuveTeam1item = new QAction(tr("Команда 1"), sceneMenuUseItem);
            aRemuveTeam1item->setCheckable(true);
            aRemuveTeam1item->setChecked(true);
            sceneMenuUseItem->addAction(aRemuveTeam1item);
            aRemuveTeam2item = new QAction(tr("Команда 2"), sceneMenuUseItem);
            aRemuveTeam2item->setCheckable(true);
            aRemuveTeam2item->setChecked(true);
            sceneMenuUseItem->addAction(aRemuveTeam2item);
            aRemuvePoints1item = new QAction(tr("Бали 1"), sceneMenuUseItem);
            aRemuvePoints1item->setCheckable(true);
            aRemuvePoints1item->setChecked(true);
            sceneMenuUseItem->addAction(aRemuvePoints1item);
            aRemuvePoints2item = new QAction(tr("Бали 2"), sceneMenuUseItem);
            aRemuvePoints2item->setCheckable(true);
            aRemuvePoints2item->setChecked(true);
            sceneMenuUseItem->addAction(aRemuvePoints2item);
            aRemuveQuestionitem = new QAction(tr("Питання"), sceneMenuUseItem);
            aRemuveQuestionitem->setCheckable(true);
            aRemuveQuestionitem->setChecked(true);
            sceneMenuUseItem->addAction(aRemuveQuestionitem);
            aRemuveTimeritem = new QAction(tr("Таймер"), sceneMenuUseItem);
            aRemuveTimeritem->setCheckable(true);
            aRemuveTimeritem->setChecked(true);
            sceneMenuUseItem->addAction(aRemuveTimeritem);
            aNothingNotUse = new QAction(tr("Всі елементи"), sceneMenuUseItem);
            aNothingNotUse->setCheckable(true);
            aNothingNotUse->setChecked(true);
            sceneMenuUseItem->addAction(aNothingNotUse);
        sceneMenuTimer = new QMenu(sceneMenu);
        sceneMenuTimer->setObjectName("sceneMenuTimer");
        sceneMenuTimer->setTitle("Таймер");
        sceneMenuTimer->setIcon(QIcon(":/new/GroupBoxes/MaterialsGroupBoxes/IconTimer.png"));
            aTimerTime = new QAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Time.png"),
                                     tr("Час"), sceneMenuTimer);
            sceneMenuTimer->addAction(aTimerTime);
            aTimerSpeed = new QAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Speed.png"),
                                      tr("Швидкість відкату"), sceneMenuTimer);
            sceneMenuTimer->addAction(aTimerSpeed);
            aTimerComeback = new QAction(tr("Відкат числа"), sceneMenuTimer);
            aTimerComeback->setObjectName("aTimerComeback");
            aTimerComeback->setCheckable(true);
            aTimerComeback->setChecked(true);
            sceneMenuTimer->addAction(aTimerComeback);
            aTimerNegativeNumbers = new QAction(tr("Від'ємні числа"), sceneMenuTimer);
            aTimerNegativeNumbers->setObjectName("aTimerNegativeNumbers");
            aTimerNegativeNumbers->setCheckable(true);
            aTimerNegativeNumbers->setChecked(true);
            sceneMenuTimer->addAction(aTimerNegativeNumbers);
            aTimerGradient = new QAction(tr("Градієнт"), sceneMenuTimer);
            aTimerGradient->setCheckable(true);
            aTimerGradient->setChecked(true);
            sceneMenuTimer->addAction(aTimerGradient);
    sceneMenu->addMenu(sceneMenuAllitem);
    sceneMenu->addMenu(sceneMenuUseItem);
    sceneMenu->addMenu(ui->menu_ItemLinePixmap);
    sceneMenu->addMenu(sceneMenuTimer);
    sceneMenu->addSeparator();
    sceneMenu->addAction(aRectAllitem);
    sceneMenu->addAction(aAutoFontQuestion);
    sceneMenu->addAction(aAutoZeroPoints);

    // добавляюем все эти действия в меню на панели меню, может кто не найдет на сцене.
    ui->menu_2->addSeparator();
    ui->menu_2->addMenu(sceneMenuAllitem);
    ui->menu_2->addMenu(sceneMenuUseItem);
    ui->menu_2->addMenu(sceneMenuTimer);
    ui->menu_2->addAction(aRectAllitem);
    ui->menu_2->addAction(aAutoFontQuestion);
    ui->menu_2->addAction(aAutoZeroPoints);

    // описываем так коннекты, чтобы они работали также и с панели меню.
    connect(sceneMenuAllitem,&QMenu::triggered,this,&SectorGraphicsView::slotSceneMenuTriggered);
    connect(sceneMenuUseItem,&QMenu::triggered,this,&SectorGraphicsView::slotSceneMenuTriggered);
    connect(sceneMenuTimer,&QMenu::triggered,this,&SectorGraphicsView::slotSceneMenuTriggered);
    // Отдельно поскольку это действие на которое нужна реакция, другие же, похожие на него, используются как флаги.
    connect(aRectAllitem,&QAction::triggered,this,&SectorGraphicsView::slotActionMenuTriggered);


}

void SectorGraphicsView::setupAndCreateMainScene()
{
    QPixmap pixmapD(10, 10);
    pixmapD.fill(QColor(color_backgroundScene_Dialog));
    pixCurentForBrushScene = pixmapD;

    pixLineTitlePixmap = QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/Bible Brain Ring (Icon).png").
                                                                    scaled(400,50,Qt::KeepAspectRatio);

    main_scene.setBackgroundBrush(QBrush(pixCurentForBrushScene));


    Item_LineTitlePixmap = new QGraphicsPixmapItem(QPixmap(pixLineTitlePixmap));
    Item_LineTitlePixmap->setFlag(QGraphicsItem::ItemIsSelectable);
    Item_LineTitlePixmap->setVisible(false);
    main_scene.addItem(Item_LineTitlePixmap);


    Doc_LineTitleText = new QTextDocument(structScreens.parentWidget);
    Doc_LineTitleText->setHtml(strItem_LineTitle);
    // Дефолт. шрифт какбы не нужен, поскольку мы используем HTML, но после сброса настроек нужно указать шрифт.
    Doc_LineTitleText->setDefaultFont(boolFontDefaultItemsReset ? QFont("Times New Roman",12)
                                                          : Doc_LineTitleText->defaultFont());
        Item_LineTitleText = new myQGraphicsTextItem(myQGraphicsTextItem::LineTitleText);
        Item_LineTitleText->setDocument(Doc_LineTitleText);
    // Для того чтобы, если после запуска сразу удалить какой-то текст, шрифт уйдет в 8.
    // Это потому что текст считался с настроек в виде Html.
    Item_LineTitleText->document()->setDefaultFont(QTextCursor(Item_LineTitleText->document()).charFormat().font());
        Item_LineTitleText->setTextWidth(400);
        Item_LineTitleText->setShow_HideRect(true);
        Item_LineTitleText->setDefaultTextColor(colorItem_LineTitle);
        main_scene.addItem(Item_LineTitleText);


    Doc_LineFirstTeam = new QTextDocument(structScreens.parentWidget);
    Doc_LineFirstTeam->setDefaultFont(boolFontDefaultItemsReset ? QFont("MS Shell Dlg 2",30,QFont::Bold)
                                                                  : Doc_LineFirstTeam->defaultFont());
    Doc_LineFirstTeam->setHtml(strItem_LineFirstTeam);
        Item_LineFirstTeam = new myQGraphicsTextItem(myQGraphicsTextItem::LineFirstTeam);
        Item_LineFirstTeam->setDocument(Doc_LineFirstTeam);
    // Обьяснение выше
    Item_LineFirstTeam->document()->setDefaultFont(QTextCursor(Item_LineFirstTeam->document()).charFormat().font());
        Item_LineFirstTeam->setTextWidth(199);
        Item_LineFirstTeam->setShow_HideRect(true);
        Item_LineFirstTeam->setDefaultTextColor(colorItem_LineFirstTeam);
        main_scene.addItem(Item_LineFirstTeam);


    Doc_LineSecondTeam = new QTextDocument(structScreens.parentWidget);
    Doc_LineSecondTeam->setDefaultFont(boolFontDefaultItemsReset ? QFont("MS Shell Dlg 2",30,QFont::Bold)
                                                                   : Doc_LineSecondTeam->defaultFont());
    Doc_LineSecondTeam->setHtml(strItem_LineSecondTeam);
        Item_LineSecondTeam = new myQGraphicsTextItem(myQGraphicsTextItem::LineSecondTeam);
        Item_LineSecondTeam->setDocument(Doc_LineSecondTeam);
    // Обьяснение выше
    Item_LineSecondTeam->document()->setDefaultFont(QTextCursor(
                                                        Item_LineSecondTeam->document()).charFormat().font());
        Item_LineSecondTeam->setTextWidth(199);
        Item_LineSecondTeam->setShow_HideRect(true);
        Item_LineSecondTeam->setDefaultTextColor(colorItem_LineSecondTeam);
        main_scene.addItem(Item_LineSecondTeam);


    Doc_LineFirstPoints = new QTextDocument(structScreens.parentWidget);
    Doc_LineFirstPoints->setDefaultFont(boolFontDefaultItemsReset ? QFont("MS Shell Dlg 2",32,QFont::Bold)
                                                                    : Doc_LineFirstPoints->defaultFont());
    Doc_LineFirstPoints->setHtml(strItem_LineFirstPoints);
        Item_LineFirstPoints = new myQGraphicsTextItem(myQGraphicsTextItem::LineFirstPoints);
        Item_LineFirstPoints->setDocument(Doc_LineFirstPoints);
    // Обьяснение выше
    Item_LineFirstPoints->document()->setDefaultFont(QTextCursor(
                                                         Item_LineFirstPoints->document()).charFormat().font());
        Item_LineFirstPoints->setTextWidth(199);
        Item_LineFirstPoints->setShow_HideRect(true);
        Item_LineFirstPoints->setDefaultTextColor(colorItem_LineFirstPoints);
        main_scene.addItem(Item_LineFirstPoints);


    Doc_LineSecondPoints = new QTextDocument(structScreens.parentWidget);
    Doc_LineSecondPoints->setDefaultFont(boolFontDefaultItemsReset ? QFont("MS Shell Dlg 2",32,QFont::Bold)
                                                                     : Doc_LineSecondPoints->defaultFont());
    Doc_LineSecondPoints->setHtml(strItem_LineSecondPoints);
        Item_LineSecondPoints = new myQGraphicsTextItem(myQGraphicsTextItem::LineSecondPoints);
        Item_LineSecondPoints->setDocument(Doc_LineSecondPoints);
    // Обьяснение выше
    Item_LineSecondPoints->document()->setDefaultFont(QTextCursor(
                                                          Item_LineSecondPoints->document()).charFormat().font());
        Item_LineSecondPoints->setTextWidth(199);
        Item_LineSecondPoints->setShow_HideRect(true);
        Item_LineSecondPoints->setDefaultTextColor(colorItem_LineSecondPoints);
        main_scene.addItem(Item_LineSecondPoints);


    Doc_LineQuestion = new QTextDocument(structScreens.parentWidget);
    Doc_LineQuestion->setDefaultFont(QFont("MS Shell Dlg 2",16,QFont::Normal));
    Doc_LineQuestion->setHtml("<font>Який цар написав багато псалмів?<br></font>");
        Item_LineQuestion = new myQGraphicsTextItem(myQGraphicsTextItem::LineQuestion);
        Item_LineQuestion->setDocument(Doc_LineQuestion);
        Item_LineQuestion->setTextWidth(400);
        Item_LineQuestion->setShow_HideRect(true);
        Item_LineQuestion->setDefaultTextColor(colorItem_LineQuestion);
        main_scene.addItem(Item_LineQuestion);




    Doc_LineTimer = new QTextDocument(structScreens.parentWidget);
    Doc_LineTimer->setDefaultFont(QFont("MS Shell Dlg 2",28,QFont::Bold));
    //хуже, чем <CENTER>...</CENTER>. Иногда Текс не переносится а заходит под, во внутрь.
    Doc_LineTimer->setDefaultTextOption(QTextOption(Qt::AlignHCenter));
    QTextCursor cursor6(Doc_LineTimer);
    cursor6.insertHtml("<b><font>&nbsp;&nbsp;&nbsp;" +
                QTime::fromMSecsSinceStartOfDay(int_timer_basic * 1000).toString("mm:ss:zzz") + "</font></b>");
        Item_LineTimer = new myQGraphicsTextItem(myQGraphicsTextItem::LineTimer);
        Item_LineTimer->setDocument(Doc_LineTimer);
        Item_LineTimer->setTextWidth(400);
        Item_LineTimer->setShow_HideRect(true);
        Item_LineTimer->setDefaultTextColor(colorItem_LineTimer);
        main_scene.addItem(Item_LineTimer);


    vecAll_Item_Line.push_back(Item_LineTitleText);
    vecAll_Item_Line.push_back(Item_LineFirstTeam);
    vecAll_Item_Line.push_back(Item_LineSecondTeam);
    vecAll_Item_Line.push_back(Item_LineFirstPoints);
    vecAll_Item_Line.push_back(Item_LineSecondPoints);
    vecAll_Item_Line.push_back(Item_LineQuestion);
    vecAll_Item_Line.push_back(Item_LineTimer);


    ui->lineEdit_0->setText(Doc_LineTitleText->toPlainText());
    ui->lineEdit_1->setText(Doc_LineFirstTeam->toPlainText());
    ui->lineEdit_2->setText(Doc_LineSecondTeam->toPlainText());
    ui->lineEdit_value_1->setText(Doc_LineFirstPoints->toPlainText());
    ui->lineEdit_value_2->setText(Doc_LineSecondPoints->toPlainText());
    ui->comboBox_question->setCurrentText("Який цар написав багато псалмів?");

    connect(ui->lineEdit_0,&QLineEdit::textChanged,this,&SectorGraphicsView::slotLineTextChanged);
    connect(ui->lineEdit_1,&QLineEdit::textChanged,this,&SectorGraphicsView::slotLineTextChanged);
    connect(ui->lineEdit_2,&QLineEdit::textChanged,this,&SectorGraphicsView::slotLineTextChanged);
    connect(ui->lineEdit_value_1,&QLineEdit::textChanged,this,&SectorGraphicsView::slotLineTextChanged);
    connect(ui->lineEdit_value_2,&QLineEdit::textChanged,this,&SectorGraphicsView::slotLineTextChanged);
    connect(ui->comboBox_question,&QComboBox::currentTextChanged,this,&SectorGraphicsView::slotLineTextChanged);
    // отображение найденного вопроса
    connect(ui->comboBox_question,SIGNAL(activated(QString)),this,SLOT(slotQuestion(QString)));


        ui->graphicsView->setScene(&main_scene);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
        main_scene.setSceneRect(0,0,400,300);
        ui->graphicsView->setRenderHint(QPainter::Antialiasing, true);
}

void SectorGraphicsView::setupAndCreateSceneSecond()
{

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------
// создание еще одной сцены которая будет устанавливаться на новое graphicsViewD и увеличиваться под другие экраны
// используются документы которые уже были созданы для главной сцены.

        sceneD.setBackgroundBrush(pixCurentForBrushScene);
        sceneD.setSceneRect(0,0,400,300);

        Item_LineTitlePixmapD = new QGraphicsPixmapItem(QPixmap(pixLineTitlePixmap));
        Item_LineTitlePixmapD->setFlag(QGraphicsItem::ItemIsSelectable);
        Item_LineTitlePixmapD->setVisible(false);
        sceneD.addItem(Item_LineTitlePixmapD);


                Item_LineTitleTextD = new myQGraphicsTextItem(myQGraphicsTextItem::LineTitleText);
                Item_LineTitleTextD->setDocument(Doc_LineTitleText);
                Item_LineTitleTextD->setTextWidth(400);
                Item_LineTitleTextD->setDefaultTextColor(colorItem_LineTitle);
                sceneD.addItem(Item_LineTitleTextD);

                Item_LineFirstTeamD = new myQGraphicsTextItem(myQGraphicsTextItem::LineFirstTeam);
                Item_LineFirstTeamD->setDocument(Doc_LineFirstTeam);
                Item_LineFirstTeamD->setTextWidth(198);
                Item_LineFirstTeamD->setDefaultTextColor(colorItem_LineFirstTeam);
                sceneD.addItem(Item_LineFirstTeamD);

                Item_LineSecondTeamD = new myQGraphicsTextItem(myQGraphicsTextItem::LineSecondTeam);
                Item_LineSecondTeamD->setDocument(Doc_LineSecondTeam);
                Item_LineSecondTeamD->setTextWidth(198);
                Item_LineSecondTeamD->setDefaultTextColor(colorItem_LineSecondTeam);
                sceneD.addItem(Item_LineSecondTeamD);

                Item_LineFirstPointsD = new myQGraphicsTextItem(myQGraphicsTextItem::LineFirstPoints);
                Item_LineFirstPointsD->setDocument(Doc_LineFirstPoints);
                Item_LineFirstPointsD->setTextWidth(198);
                Item_LineFirstPointsD->setDefaultTextColor(colorItem_LineFirstPoints);
                sceneD.addItem(Item_LineFirstPointsD);

                Item_LineSecondPointsD = new myQGraphicsTextItem(myQGraphicsTextItem::LineSecondPoints);
                Item_LineSecondPointsD->setDocument(Doc_LineSecondPoints);
                Item_LineSecondPointsD->setTextWidth(198);
                Item_LineSecondPointsD->setDefaultTextColor(colorItem_LineSecondPoints);
                sceneD.addItem(Item_LineSecondPointsD);

                Item_LineQuestionD = new myQGraphicsTextItem(myQGraphicsTextItem::LineQuestion);
                Item_LineQuestionD->setDocument(Doc_LineQuestion);
                Item_LineQuestionD->setTextWidth(400);
                Item_LineQuestionD->setDefaultTextColor(colorItem_LineQuestion);
                sceneD.addItem(Item_LineQuestionD);

                Item_LineTimerD = new myQGraphicsTextItem(myQGraphicsTextItem::LineTimer);
                Item_LineTimerD->setDocument(Doc_LineTimer);
                Item_LineTimerD->setTextWidth(400);
                Item_LineTimerD->setDefaultTextColor(colorItem_LineTimer);
                sceneD.addItem(Item_LineTimerD);

                vecAll_Item_LineD.push_back(Item_LineTitleTextD);
                vecAll_Item_LineD.push_back(Item_LineFirstTeamD);
                vecAll_Item_LineD.push_back(Item_LineSecondTeamD);
                vecAll_Item_LineD.push_back(Item_LineFirstPointsD);
                vecAll_Item_LineD.push_back(Item_LineSecondPointsD);
                vecAll_Item_LineD.push_back(Item_LineQuestionD);
                vecAll_Item_LineD.push_back(Item_LineTimerD);
    for (int var = 0; var < vecAll_Item_LineD.size(); ++var)
        vecAll_Item_LineD[var]->setData(1,int(var)); // необходимо чтобы цвет не терялся когда текст.док. пустой

        // увеличиваем изображение только однажды. Последущее увеличение происходит только через настройки.
        for (int var = 0; var < structScreens.VecGraphicsViewDesktop.size(); ++var)
        {
            structScreens.VecGraphicsViewDesktop[var]->setScene(&sceneD);
            structScreens.VecGraphicsViewDesktop[var]->scale(structScreens.VecGraphicsViewScaleSize[var].width(),
                                               structScreens.VecGraphicsViewScaleSize[var].height());
        }

//-------------------------------------------------------------------------------------------------------
//-------------------------------------------------------------------------------------------------------

        slotRefresh_ItemPos(); // установка каждого (ItemLine... - главных) на свое место
        slotOnToolButton_plus_2_clicked();// Вызываю 3 раза поднятие элементов чтобы коректно выглядели.
        slotOnToolButton_plus_2_clicked();
        slotOnToolButton_plus_2_clicked();// Сделал так поскольку уже боюсь что-то испортить.


//  slotRefresh_ItemPos() - не только обновляется позиция элементов, а и обновление текста в (LineEdit...)
connect(Item_LineTitleText->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
connect(Item_LineFirstTeam->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
connect(Item_LineSecondTeam->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
connect(Item_LineFirstPoints->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
connect(Item_LineSecondPoints->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
connect(Item_LineQuestion->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
connect(Item_LineTimer->document(),&QTextDocument::contentsChanged,this,&SectorGraphicsView::slotRefresh_ItemPos);
   connect(Item_LineTitleText,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);
   connect(Item_LineFirstTeam,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);
   connect(Item_LineSecondTeam,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);
   connect(Item_LineFirstPoints,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);
   connect(Item_LineSecondPoints,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);
   connect(Item_LineQuestion,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);
   connect(Item_LineTimer,&myQGraphicsTextItem::cursorPositionChangeD,this,&SectorGraphicsView::slotRefresh_Tool);

connect(&main_scene,&QGraphicsScene::focusItemChanged,this,&SectorGraphicsView::slotfocusItemChanged);



connect(ui->graphicsView,&QGraphicsView::customContextMenuRequested,this,&SectorGraphicsView::slotSceneMenuExec);
}

void SectorGraphicsView::setupPushButton_color()
{
    QPixmap pixIconColor(100,100);
    pixIconColor.fill(QColor(color_backgroundScene_Dialog));
    QIcon icon(pixIconColor);
    ui->pushButton_color->setIcon(icon);
    ui->pushButton_color->setIconSize(QSize(20,20));
}

void SectorGraphicsView::slotSceneMenuExec(const QPoint &pos)
{
    sceneMenu->exec(ui->graphicsView->mapToGlobal(pos));
}

void SectorGraphicsView::slotActionMenuTriggered(bool)
{
    QAction *sceenAction = qobject_cast<QAction *>(sender());
    slotSceneMenuTriggered(sceenAction);
}

void SectorGraphicsView::slotSceneMenuTriggered(QAction *action)
{
//    QAction *sceenAction = qobject_cast<QAction *>(sender()); // для запоминания. Можно удалить
    QAction *sceenAction = action;

    if(sceenAction->text() == "Описувати квадрати")
    {
        foreach (myQGraphicsTextItem *item, vecAll_Item_Line)
            item->setShow_HideRect(sceenAction->isChecked());
    }
    else if(sceenAction->text() == "Шрифт")
    {
        ui->graphicsView->setFocus();
            bool ok;
            QFont font = QFontDialog::getFont(&ok);
            if(!ok) return;
        QTextCharFormat fontFormat;
        fontFormat.setFont(font);
        foreach (myQGraphicsTextItem *item, vecAll_Item_Line)
        {
            QTextCursor cursor = item->textCursor();
            cursor.select(QTextCursor::Document);
            cursor.mergeCharFormat(fontFormat);
            cursor.clearSelection();
            item->setTextCursor(cursor);
            item->document()->setDefaultFont(font);
        }
    }
    else if(sceenAction->text() == "Колір")
    {
        QColor color = QColorDialog::getColor(Qt::white);
        if(!color.isValid())
            return;
        QTextCharFormat foregroundFormat;
        foregroundFormat.setForeground(QBrush(color));
        foreach (myQGraphicsTextItem *item, vecAll_Item_Line)
        {
            QTextCursor cursor = item->textCursor();
            cursor.select(QTextCursor::Document);
            cursor.mergeCharFormat(foregroundFormat);
            cursor.clearSelection();
            item->setTextCursor(cursor);
            item->setDefaultTextColor(color);
            vecAll_Item_LineD[item->data(1).toInt()]->setDefaultTextColor(color);
        }
    }
    else if(sceenAction->text() == "Колір Фона"){
        slotOnPushButton_color_clicked();
    }

    else if(sceenAction->text() == "Всі елементи"){// Сначала заходим сюда, а потом по очереди
        aRemuveTitlePixmapItem->setChecked(false);
        aRemuveTitleTextItem->setChecked(aNothingNotUse->isChecked());
        aRemuveTeam1item->setChecked(aNothingNotUse->isChecked());
        aRemuveTeam2item->setChecked(aNothingNotUse->isChecked());
        aRemuvePoints1item->setChecked(aNothingNotUse->isChecked());
        aRemuvePoints2item->setChecked(aNothingNotUse->isChecked());
        aRemuveQuestionitem->setChecked(aNothingNotUse->isChecked());
        aRemuveTimeritem->setChecked(aNothingNotUse->isChecked());
    }
    if(sceenAction->text() == "Заголовок зображення" || sceenAction->text() == "Всі елементи"){
        Item_LineTitlePixmap->setVisible(aRemuveTitlePixmapItem->isChecked());
        Item_LineTitlePixmapD->setVisible(aRemuveTitlePixmapItem->isChecked());}
    if(sceenAction->text() == "Заголовок текст" || sceenAction->text() == "Всі елементи"){
        Item_LineTitleText->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineTitleTextD->setVisible(sceenAction->isChecked() ? true : false);}
    if(sceenAction->text() == "Команда 1" || sceenAction->text() == "Всі елементи"){
        Item_LineFirstTeam->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineFirstTeamD->setVisible(sceenAction->isChecked() ? true : false);}
    if(sceenAction->text() == "Команда 2" || sceenAction->text() == "Всі елементи"){
        Item_LineSecondTeam->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineSecondTeamD->setVisible(sceenAction->isChecked() ? true : false);}
    if(sceenAction->text() == "Бали 1" || sceenAction->text() == "Всі елементи"){
        Item_LineFirstPoints->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineFirstPointsD->setVisible(sceenAction->isChecked() ? true : false);}
    if(sceenAction->text() == "Бали 2" || sceenAction->text() == "Всі елементи"){
        Item_LineSecondPoints->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineSecondPointsD->setVisible(sceenAction->isChecked() ? true : false);}
    if(sceenAction->text() == "Питання" || sceenAction->text() == "Всі елементи"){
        Item_LineQuestion->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineQuestionD->setVisible(sceenAction->isChecked() ? true : false);}
    if(sceenAction->text() == "Таймер" || sceenAction->text() == "Всі елементи")
    {
        Item_LineTimer->setVisible(sceenAction->isChecked() ? true : false);
        Item_LineTimerD->setVisible(sceenAction->isChecked() ? true : false);
        ui->checkBox_timer->setChecked(sceenAction->isChecked());
    }


    if(sceenAction->text() == "Час"){
        emit aTimeToActionSceneMenuTimerTimeTriggered();
    }
    if(sceenAction->text() == "Швидкість відкату"){
        emit aSpeedToActionSceneMenuTimerSpeedTriggered();
    }

    slotRefresh_ItemPos(); // думаю это никому не будет мешать

}

void SectorGraphicsView::writeTextChanged_on_Item_Line(myQGraphicsTextItem *Item, const int pos, const QString &str)
{
    QTextCursor cursor(Item->document());

            // Чтобы при пустом документе все настройки не уходили в дефолт.
            if(str == ""){
                Item->document()->setDefaultFont(cursor.charFormat().font());
            }

cursor.beginEditBlock(); // очень важная вещь

        cursor.movePosition(QTextCursor::Start);
        cursor.movePosition(QTextCursor::NextCharacter,QTextCursor::MoveAnchor,pos+1); // доделать в конце +1
            QTextCharFormat charFormat;
            charFormat.setFont(QFont(cursor.charFormat().font()));
            charFormat.setForeground(Item->textCursor().charFormat().foreground());
            QTextBlockFormat blockFormat;
            blockFormat.setAlignment(Qt::AlignHCenter);
            cursor.document()->clear();// Именно очищать нужно.
        cursor.insertText(str,charFormat);
        cursor.mergeCharFormat(charFormat);
            if(Item != Item_LineQuestion)
        cursor.mergeBlockFormat(blockFormat);
cursor.endEditBlock();

        Item->setTextCursor(cursor);
}

void SectorGraphicsView::slotWriteTextChanged_on_TimerItem(int int_SecondsTimer_changing_now, QString strTimer)
{
    QTextCursor cursor(Item_LineTimer->document());
cursor.beginEditBlock();// очень важная вещь
        cursor.movePosition(QTextCursor::End);
            QTextCharFormat charFormat;
            charFormat.setFont(cursor.charFormat().font());
            charFormat.setForeground(cursor.charFormat().foreground());


//          Все рисуется стандартным цветом. Если нужно другой, дальше это делается.
            charFormat.setForeground(Item_LineTimer->defaultTextColor());

                QRgb rgb = qRgb(250,0,0);// Это подготовленный красный цвет, если что то он вставится.
                // Если включен градиент он будет действовать только на цифры 3,2,1,0
                if(int_SecondsTimer_changing_now <= 3 && int_SecondsTimer_changing_now >= 0
                        && aTimerGradient->isChecked())
                {
                    QLinearGradient LinearGradient(0, 0, 210, 10);
                    LinearGradient.setColorAt(0,cursor.charFormat().foreground().color());//Здесь смещается градиент.
                    LinearGradient.setColorAt(1,QColor(250,0,0));

                        QImage image(210,10, QImage::Format_RGB32);
                        QPainter painter(&image);
                        painter.setBrush(LinearGradient);
                        painter.drawRect(image.rect());

                        // Из-за того что часто вызывается функция, градиент смещается, поэтому одной этой -
                        rgb = image.pixel(3,5);// - строки достаточно.

                        charFormat.setForeground(QBrush(QColor(rgb)));
                }

                // Если ниже нуля, всегда красный несмотря на то что включен градиент или нет.
                if(int_SecondsTimer_changing_now < 0)
                    charFormat.setForeground(QBrush(QColor(rgb)));


            QTextBlockFormat blockFormat;
            blockFormat.setAlignment(Qt::AlignHCenter);
        Item_LineTimer->document()->clear();
        cursor.insertText(strTimer,charFormat);
        cursor.mergeBlockFormat(blockFormat);
cursor.endEditBlock();

    Item_LineTimer->setTextCursor(cursor);
}


void SectorGraphicsView::refreshPosOtherScreens()
{
    Item_LineTitlePixmapD->setPos(Item_LineTitlePixmap->pos());

        Item_LineTitleTextD->setPos(Item_LineTitleText->pos());

        Item_LineFirstTeamD->setPos(Item_LineFirstTeam->pos());

        Item_LineFirstPointsD->setPos(Item_LineFirstPoints->pos());

        Item_LineSecondTeamD->setPos(Item_LineSecondTeam->pos());

        Item_LineSecondPointsD->setPos(Item_LineSecondPoints->pos());

        Item_LineQuestionD->setPos(Item_LineQuestion->pos());

        Item_LineTimerD->setPos(Item_LineTimer->pos());
}


QPixmap SectorGraphicsView::createColorToolButtonIcon(QColor color)
{
    QPixmap pixmap(50, 80);
    pixmap.fill(Qt::transparent);
    QPainter painter(&pixmap);
    QPixmap image(":/new/ActionImage/ActionImageScene/textpointer.png");
    QRect target (0, 0, 50, 60);
    QRect source(0, 0, 42, 42);
    painter.fillRect(QRect(0, 60, 50, 180), color);
    painter.drawPixmap(target, image, source);

    return pixmap;
}


QMenu *SectorGraphicsView::createColorMenu(QColor defaultColor)
{
    QList<QColor> colors;
    colors << Qt::black << Qt::white << Qt::red << Qt::blue << Qt::yellow;
    QStringList names;
    names << tr("black") << tr("white") << tr("red") << tr("blue") << tr("yellow");

    QMenu *colorMenu = new QMenu;
    for (int i = 0; i < colors.count(); ++i)
    {
                            QPixmap pixmap(20, 20);
                            QPainter painter(&pixmap);
                            painter.setPen(Qt::NoPen);
                            painter.fillRect(QRect(0, 0, 20, 20), colors.at(i));
        QAction *action = new QAction(names.at(i), structScreens.parentWidget);
        action->setData(colors.at(i));
        action->setIcon(QIcon(pixmap));
            connect(action, SIGNAL(triggered()),this,SLOT(textColorChanged()));
        colorMenu->addAction(action);
            if (colors.at(i) == defaultColor)
                colorMenu->setDefaultAction(action);
    }
        QAction *action = new QAction(tr("Другой..."), structScreens.parentWidget);
        action->setData("more");
        action->setIcon(QIcon(QPixmap(":/new/ActionImage/ActionImageScene/colors.png")));
            connect(action, SIGNAL(triggered()),this, SLOT(textColorChanged()));
        colorMenu->addAction(action);

    return colorMenu;
}


void SectorGraphicsView::textColorChanged()
{
    // эта фунция должна вызываться только по причине активации контекстного меню
    // здесь перерисовывается картинка(А) и под ней меняется цвет соотвецтвенно выбору пользователя
    QAction *textAction = qobject_cast<QAction *>(sender());
    if(textAction->text() == "Другой...")
    {
        QColor color = QColorDialog::getColor(Qt::black);
        ui->toolButton_color_2->setIcon(createColorToolButtonIcon(color));
        ui->toolButton_color_2->menu()->setDefaultAction(textAction);
        ui->toolButton_color_2->menu()->defaultAction()->setData(color);
        slotOnToolButton_color_2_clicked();
        return;
    }

    ui->toolButton_color_2->setIcon(createColorToolButtonIcon(qvariant_cast<QColor>(textAction->data())));
    ui->toolButton_color_2->menu()->setDefaultAction(textAction);
    slotOnToolButton_color_2_clicked();
}

void SectorGraphicsView::ffRefresh_ItemPos()
{
// выщитывается позиций квадратов и передвижение их.

        static int aa = 3,a = 3,b = 3,c = 3,d = 3,f = 3,g = 3, w = 0;
        if(slotIsFocusItem() == 0 && !Item_LineTitlePixmap->isSelected())
        {
            if(intIntervalPlusMinus != 0)
            w = 0,aa = a = b = c = d = f = g += intIntervalPlusMinus;// здесь спасает +=, в отличии от (w)
            // обнуление происходит если нажат плюс или минус, но не при редакции текста
        }
        else
        {
            if(Item_LineTitlePixmap->isSelected() && Item_LineTitlePixmap->isVisible())
                aa += intIntervalPlusMinus;
            else if(Item_LineTitleText->boolFocusInOut)
                a += intIntervalPlusMinus;
            else if(Item_LineFirstTeam->boolFocusInOut)
                b += intIntervalPlusMinus;
            else if(Item_LineSecondTeam->boolFocusInOut)
                c += intIntervalPlusMinus;
            else if(Item_LineFirstPoints->boolFocusInOut)
                d += intIntervalPlusMinus;
            else if(Item_LineSecondPoints->boolFocusInOut)
                f += intIntervalPlusMinus;
            else if(Item_LineQuestion->boolFocusInOut)
                g += intIntervalPlusMinus;
            else if(Item_LineTimer->boolFocusInOut)
                w += intIntervalPlusMinus;
        }
        // isVisible() для того чтобы контролировать "использовать элементы" в контекстном меню
        int heightTitlePix = Item_LineTitlePixmap->isVisible() ? Item_LineTitlePixmap->boundingRect().height()+aa:0;
        int heightTitleText = Item_LineTitleText->isVisible() ? Item_LineTitleText->boundingRect().height()+a : 0;
        int heightFirstTeam = Item_LineFirstTeam->isVisible() ? Item_LineFirstTeam->boundingRect().height()+b : 0;
        int heightSecondTeam = Item_LineSecondTeam->isVisible() ? Item_LineSecondTeam->boundingRect().height()+c : 0;
        int heightFirstPoints = Item_LineFirstPoints->isVisible() ? Item_LineFirstPoints->boundingRect().height()+d:0;
        int heightSecondPoints =Item_LineSecondPoints->isVisible()?Item_LineSecondPoints->boundingRect().height()+f:0;
        int heightQuestion = Item_LineQuestion->isVisible() ? Item_LineQuestion->boundingRect().height()+g : 0;
            int hTP = heightTitlePix + heightTitleText;
            int hTfT = heightTitlePix + heightTitleText + heightFirstTeam;
            int hTsT = heightTitlePix + heightTitleText + heightSecondTeam;
            int hTfT_FP = heightTitlePix + heightTitleText + heightFirstTeam + heightFirstPoints;
            int hTsT_SP = heightTitlePix + heightTitleText + heightSecondTeam + heightSecondPoints;
        Item_LineTitlePixmap->setPos(200 - Item_LineTitlePixmap->pixmap().width()/2,0+w);
        // передвигается точка отсчета, как  на выше и ниже строке
        Item_LineTitleText->setPos(0,Item_LineTitlePixmap->isVisible() ? 0+heightTitlePix : 0+heightTitlePix + w);
        Item_LineFirstTeam->setPos(0,hTP);
        Item_LineSecondTeam->setPos(201,hTP);
        Item_LineFirstPoints->setPos(0,hTfT);
        Item_LineSecondPoints->setPos(201,hTsT);
        Item_LineQuestion->setPos(0,hTfT_FP > hTsT_SP ? hTfT_FP : hTsT_SP);
        Item_LineTimer->setPos(0, hTfT_FP + heightQuestion > hTsT_SP + heightQuestion
                               ? hTfT_FP + heightQuestion : hTsT_SP + heightQuestion);
                    intIntervalPlusMinus = 0; // обнуление

}

void SectorGraphicsView::slotRefresh_ItemPos()
{
//------------------------------------------------------------------------------------------------------
// отделил в отдельную функцию. Сначала не было так.

                ffRefresh_ItemPos();


//------------------------------------------------------------------------------------------------------
// другие экраны

                refreshPosOtherScreens();

//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Для того чтобы при пустом документе все настройки не уходили в дефолт. Слишком тяжело для пониания и обьяснения.

                if(slotIsFocusItem() == 0) return;// Выходим если пишеться не в сцене.
                myQGraphicsTextItem *myItem = slotIsFocusItem();

                static bool boolEnter = true;
                if(myItem->document()->isEmpty() && boolEnter)
                {
                    boolEnter = false;
                    QTextCursor cursorMyItem(myItem->document());
                    cursorMyItem.beginEditBlock();
                        QTextCharFormat charFormat;
                        charFormat.setFont(myItem->document()->defaultFont());
                        QTextBlockFormat blockFormat;
                        blockFormat.setAlignment(Qt::AlignHCenter);
                        cursorMyItem.document()->clear();// Именно очищать нужно.
                    cursorMyItem.mergeCharFormat(charFormat);
                        if(myItem != Item_LineQuestion)
                    cursorMyItem.mergeBlockFormat(blockFormat);
                    cursorMyItem.endEditBlock();
                }
                else
                {
                    boolEnter = true;
                    myItem->document()->setDefaultFont(QTextCursor(myItem->document()).charFormat().font());
                }

//qDebug() << "Text isEmpty0" << myItem->document()->defaultFont().pointSize() <<endl;
//        qDebug() << "Text isEmpty1 " << QTextCursor(myItem->document()).charFormat().fontPointSize() <<endl;
//qDebug() << "Text isEmpty0" << QTextCursor(myItem->document()).blockFormat().alignment() <<endl;
//        qDebug() << "Text isEmpty0" << myItem->document()->defaultTextOption().alignment() <<endl;
// Не удалять. Это все по-разному почему-то работает.


//------------------------------------------------------------------------------------------------------
//------------------------------------------------------------------------------------------------------
// Здесь происходит утановка текста на (ui->lineEdit...) в ответ на изменения в (Item_Line...).
// Обьеденил все здесь, очень надеюсь одно не будет мешать другому. Таймер здесь не учавствует

//                if(slotIsFocusItem() == 0) return; // выше проверка есть
            if(Item_LineTitleText->boolFocusInOut)
                ui->lineEdit_0->setText(Item_LineTitleText->document()->toPlainText());
            else if(Item_LineFirstTeam->boolFocusInOut){
                ui->lineEdit_1->setText(Item_LineFirstTeam->document()->toPlainText());
                // Первое условие чтобы не было рекурсии. Второе смотрим флаг.
                if(ui->lineEdit_value_1->text() != "0" && aAutoZeroPoints->isChecked()){
                    ui->lineEdit_value_1->setText("0");// Обнуление очков при редактировании команды
                    writeTextChanged_on_Item_Line(Item_LineFirstPoints,0,"0");
                }
            }
            else if(Item_LineSecondTeam->boolFocusInOut){
                ui->lineEdit_2->setText(Item_LineSecondTeam->document()->toPlainText());
                if(ui->lineEdit_value_2->text() != "0" && aAutoZeroPoints->isChecked()){
                    ui->lineEdit_value_2->setText("0");// Обнуление очков при редактировании команды
                    writeTextChanged_on_Item_Line(Item_LineSecondPoints,0,"0");
                }
            }
            else if(Item_LineFirstPoints->boolFocusInOut)
                ui->lineEdit_value_1->setText(Item_LineFirstPoints->document()->toPlainText());
            else if(Item_LineSecondPoints->boolFocusInOut)
                ui->lineEdit_value_2->setText(Item_LineSecondPoints->document()->toPlainText());
            else if(Item_LineQuestion->boolFocusInOut)
                ui->comboBox_question->setCurrentText(Item_LineQuestion->document()->toPlainText());


            slotRefresh_Tool();

}

void SectorGraphicsView::slotRefresh_Tool()
{
    if(slotIsFocusItem() == 0)
        return;
  QTextCharFormat charFormat = slotIsFocusItem()->textCursor().charFormat();
  ui->toolButton_Bold_2->setChecked(charFormat.font().bold());
  ui->toolButton_Italic_2->setChecked(charFormat.font().italic());
  ui->toolButton_Underline_2->setChecked(charFormat.font().underline());
    if(ui->fontSizeCombo_2->findText(QString::number(charFormat.font().pointSize())) != -1)
  ui->fontSizeCombo_2->setCurrentIndex(ui->fontSizeCombo_2->findText(
                                           QString::number(charFormat.font().pointSize())));
    else
  ui->fontSizeCombo_2->setEditText(QString::number(charFormat.font().pointSize()));

}


myQGraphicsTextItem *SectorGraphicsView::slotIsFocusItem()
{
    myQGraphicsTextItem *item;
    if(Item_LineTitleText->boolFocusInOut)
        item = Item_LineTitleText;
    else if(Item_LineFirstTeam->boolFocusInOut)
        item = Item_LineFirstTeam;
    else if(Item_LineSecondTeam->boolFocusInOut)
        item = Item_LineSecondTeam;
    else if(Item_LineFirstPoints->boolFocusInOut)
        item = Item_LineFirstPoints;
    else if(Item_LineSecondPoints->boolFocusInOut)
        item = Item_LineSecondPoints;
    else if(Item_LineQuestion->boolFocusInOut)
        item = Item_LineQuestion;
    else if(Item_LineTimer->boolFocusInOut)
        item = Item_LineTimer;
    else
        return 0;

    return item;
}

void SectorGraphicsView::slotfocusItemChanged(QGraphicsItem *newFocus, QGraphicsItem *oldFocus, Qt::FocusReason reason)
{
    Q_UNUSED(newFocus); Q_UNUSED(reason);
    if(Item_LineTitlePixmap->isSelected())
    {
        Item_LineTitlePixmap->setFlag(QGraphicsItem::ItemIsSelectable,false);
        Item_LineTitlePixmap->setFlag(QGraphicsItem::ItemIsSelectable,true);
    }
        if(oldFocus == 0 /*для первого запуска приложения*/) return;
        QTextCursor cursor = qgraphicsitem_cast<myQGraphicsTextItem *> (oldFocus)->textCursor();
            if(main_scene.hasFocus() && cursor.hasSelection())
            cursor.clearSelection();
        qgraphicsitem_cast<myQGraphicsTextItem *> (oldFocus)->setTextCursor(cursor);
}

void SectorGraphicsView::slotSetFont()
{
        bool ok;
        QFont font = QFontDialog::getFont(&ok,slotIsFocusItem() != 0 ? slotIsFocusItem()->font() : QFont());
        if(!ok) return;
    if(slotIsFocusItem() == 0) return;
    QTextCursor cursor = slotIsFocusItem()->textCursor();
    QTextCharFormat charFormat;
    charFormat.setFont(font);
    cursor.mergeCharFormat(charFormat);
    slotIsFocusItem()->setTextCursor(cursor);
    slotRefresh_Tool();
}

void SectorGraphicsView::slotLineTextChanged(const QString str)
{
    if(ui->lineEdit_0->hasFocus())
        writeTextChanged_on_Item_Line(Item_LineTitleText,ui->lineEdit_0->cursorPosition(),str);
    else if(ui->lineEdit_1->hasFocus()){
        writeTextChanged_on_Item_Line(Item_LineFirstTeam,ui->lineEdit_1->cursorPosition(),str);
        if(aAutoZeroPoints->isChecked()){// Обнуление очков при редактировании команды
            writeTextChanged_on_Item_Line(Item_LineFirstPoints,0,"0");
            ui->lineEdit_value_1->setText("0");
        }
    }
    else if(ui->lineEdit_2->hasFocus()){
        writeTextChanged_on_Item_Line(Item_LineSecondTeam,ui->lineEdit_2->cursorPosition(),str);
        if(aAutoZeroPoints->isChecked()){// Обнуление очков при редактировании команды
            writeTextChanged_on_Item_Line(Item_LineSecondPoints,0,"0");
            ui->lineEdit_value_2->setText("0");
        }
    }
    else if(ui->lineEdit_value_1->hasFocus())
        writeTextChanged_on_Item_Line(Item_LineFirstPoints,ui->lineEdit_value_1->cursorPosition(),str);
    else if(ui->lineEdit_value_2->hasFocus())
        writeTextChanged_on_Item_Line(Item_LineSecondPoints,ui->lineEdit_value_2->cursorPosition(),str);
    else if(ui->comboBox_question->lineEdit()->hasFocus())
        writeTextChanged_on_Item_Line(Item_LineQuestion,ui->comboBox_question->lineEdit()->cursorPosition(),str);
}


void SectorGraphicsView::slotQuestion(const QString &str)
{// Сюда заходим если комбобокс вызвал, при выборе из списка. Когда редактируется комбобокс сюда не входим.

    QString strCopy = str;// Создаем копию, чтобы можно было удалить теги.
    QRegExp rxHTML("(<span style=\"background: yellow\">|</span>)");
    if(rxHTML.indexIn(str, 0) != -1){// Если теги были найдены мы их удалим. И еще это от рекурсии.
        strCopy.remove(rxHTML);// Очищаем теги
        ui->comboBox_question->lineEdit()->setText(strCopy);// Устанавливаем очищеный текст и на комбобокс.
    }

    Item_LineQuestion->setPlainText(strCopy);// Устанавливаем текст.

// Автоматический шрифт вопроса.

// Подбор шрифта происходит лишь в том случае если не отключен вопрос. Происходит это так, у последнего элемента,
// Item_LineTimer узнается его положение и если оно выходит за граниуцы сцены или нет, мы меняем шрифт вопроса.
// А если таймер отключен тогда мы ориентируемся по Item_LineQuestion. Если же и он отключен тогда мы вообще не
// входим сюда.
    // Если не скрыт вопрос, не пустая строка, и есть влажек на использование алгоритма aAutoFontQuestion.
    if(Item_LineQuestion->isVisible() && !strCopy.isEmpty() && aAutoFontQuestion->isChecked())
    {
        // Определяется относительно чего ориентироваться, Item_LineTimer или Item_LineQuestion.
        myQGraphicsTextItem *ItemTimerOrQuestion = Item_LineTimer->isVisible() ? Item_LineTimer : Item_LineQuestion;
        QTextCursor cursor = Item_LineQuestion->textCursor();
        cursor.select(QTextCursor::Document);
        QTextCharFormat PointSizeFormat;

        if(ItemTimerOrQuestion->pos().y() + ItemTimerOrQuestion->boundingRect().height() < 300)
        {// Если еще место есть, тогда увеличиваем шрифт.
            PointSizeFormat.setFontPointSize(cursor.charFormat().font().pointSize() + 1);
            cursor.mergeCharFormat(PointSizeFormat);
            Item_LineQuestion->setTextCursor(cursor);

            // Если вышли за границы сцены, тогда используем этот шрифт только -1.
            if(ItemTimerOrQuestion->pos().y() + ItemTimerOrQuestion->boundingRect().height() > 300){
                PointSizeFormat.setFontPointSize(cursor.charFormat().font().pointSize() - 1);
                cursor.mergeCharFormat(PointSizeFormat);
                Item_LineQuestion->setTextCursor(cursor);
                cursor.clearSelection();// Очищаем выделение, хотя это и так понятно.
                Item_LineQuestion->setTextCursor(cursor);
                return;
            }
            slotQuestion(strCopy);// Происходит все рекурсивно.
        }
        if(ItemTimerOrQuestion->pos().y() + ItemTimerOrQuestion->boundingRect().height() > 300)
        {// Если вышли за границы сцены, тогда уменьшаем шрифт.
            PointSizeFormat.setFontPointSize(cursor.charFormat().font().pointSize() - 1);
            cursor.mergeCharFormat(PointSizeFormat);
            Item_LineQuestion->setTextCursor(cursor);

            // Если уменьшили размер и нет выхода за границы, тогда оставляем текущий шрифт.
            if(ItemTimerOrQuestion->pos().y() + ItemTimerOrQuestion->boundingRect().height() <= 300){
                cursor.clearSelection();// Очищаем выделение, хотя это и так понятно.
                Item_LineQuestion->setTextCursor(cursor);
                return;
            }
            slotQuestion(strCopy);
        }
    }
}

void SectorGraphicsView::slotSetLoadPixmap()
{
    QString strFilter;
    QString str = QFileDialog::getOpenFileName(0,tr("Open Pixmap"), QDir::currentPath(),
            "Images (*.png *.jpg *.jpeg)"
            ";;  *.jpg", &strFilter);

    if (!str.isEmpty())
    {
        QSize sezePix = pixLineTitlePixmap.size();
        pixLineTitlePixmap = QPixmap(str).scaled(sezePix,Qt::KeepAspectRatio);
        Item_LineTitlePixmap->setPixmap(pixLineTitlePixmap);
        Item_LineTitlePixmapD->setPixmap(pixLineTitlePixmap);
    }
}

void SectorGraphicsView::slotSetItemPixmapSize()
{
    QDialog dialog;
    dialog.setWindowFlags(Qt::WindowCloseButtonHint);

    QLabel *labelW = new QLabel(&dialog);
    labelW->setText("Width:");
        QLabel *labelH = new QLabel(&dialog);
        labelH->setText("Height:");
    QSpinBox *spinBoxW = new QSpinBox(&dialog);
    spinBoxW->setMinimumHeight(45);
    spinBoxW->setMaximum(1000);
    spinBoxW->setValue(400);
    spinBoxW->setEnabled(false);
        QSpinBox *spinBoxH = new QSpinBox(&dialog);
        spinBoxH->setMinimumHeight(45);
        spinBoxH->setMaximum(1000);
        spinBoxH->setValue(pixLineTitlePixmap.height());

    QPushButton *pushButton1 = new QPushButton(&dialog);
    pushButton1->setText("Ok");
    QPushButton *pushButton2 = new QPushButton(&dialog);
    pushButton2->setText("Cancel");

    QGridLayout gridLayout;
    gridLayout.addWidget(labelW,0,0);
    gridLayout.addWidget(labelH,0,1);
    gridLayout.addWidget(spinBoxW,1,0);
    gridLayout.addWidget(spinBoxH,1,1);
    gridLayout.addWidget(pushButton1,2,0);
    gridLayout.addWidget(pushButton2,2,1);
    dialog.setLayout(&gridLayout);

    connect(pushButton1,SIGNAL(clicked()),&dialog,SLOT(accept()));
    connect(pushButton2,SIGNAL(clicked()),&dialog,SLOT(reject()));
    if(dialog.exec() == QDialog::Accepted)
    {
        QPixmap copyPixmap;
        copyPixmap = pixLineTitlePixmap;
        pixLineTitlePixmap = copyPixmap.scaled(spinBoxW->value(),
                                                                   spinBoxH->value(),Qt::KeepAspectRatio);
        Item_LineTitlePixmap->setPixmap(pixLineTitlePixmap);
        Item_LineTitlePixmapD->setPixmap(pixLineTitlePixmap);
        slotRefresh_ItemPos();
    }
}

void SectorGraphicsView::slotSettingsScreens()
{
    QDialogSettingsScreens dialogSettingsScreens(structScreens);
    if(dialogSettingsScreens.exec() != QDialog::Accepted){
        return;
    }
    refreshPosOtherScreens();
}


void SectorGraphicsView::slotSetBackgroundBrush(QPixmap pixCurent)
{
    if(pixCurent.isNull()){ // Это нужно для обработки нажатия на OnRadioButton_2_clicked.
        pixCurent = QPixmap(10,10);
        pixCurent.fill(QColor(color_backgroundScene_Dialog));
    }
    pixCurentForBrushScene = pixCurent;
    main_scene.setBackgroundBrush(QBrush(pixCurentForBrushScene));
    sceneD.setBackgroundBrush(QBrush(pixCurentForBrushScene));
    refreshPosOtherScreens();
}

void SectorGraphicsView::slotOnPushButton_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::black);
    if (color.isValid())
    {
        color_backgroundScene_Dialog = color;
        QPixmap pixIconColor(100,100);
        pixIconColor.fill(QColor(color_backgroundScene_Dialog));
        ui->pushButton_color->setIcon(QIcon(pixIconColor));

        if(ui->radioButton_2->isChecked()){
            QPixmap pixCurent(10,10);
            pixCurent.fill(QColor(color_backgroundScene_Dialog));
            slotSetBackgroundBrush(pixCurent);
        }
    }
}

void SectorGraphicsView::slotOnCheckBox_timer_clicked(bool checked)
{
    aRemuveTimeritem->setChecked(checked);
    Item_LineTimer->setVisible(checked);
    Item_LineTimerD->setVisible(checked);
}


void SectorGraphicsView::slotOnToolButton_plus_2_clicked()
{
    intIntervalPlusMinus = -1;
    slotRefresh_ItemPos();
}

void SectorGraphicsView::slotOnToolButton_minus_2_clicked()
{
    intIntervalPlusMinus = 1;
    slotRefresh_ItemPos();
}

void SectorGraphicsView::slot_fontSizeCombo_highlighted_AND_activated(int index)
{
    ui->graphicsView->setFocus();
    if(slotIsFocusItem() == 0)
        return;

    QTextCursor cursor = slotIsFocusItem()->textCursor();
    QTextCharFormat PointSizeFormat;
    PointSizeFormat.setFontPointSize(ui->fontSizeCombo_2->itemText(index).toInt());
    cursor.mergeCharFormat(PointSizeFormat);
    slotIsFocusItem()->setTextCursor(cursor);
}

void SectorGraphicsView::slotOnToolButton_Bold_2_clicked(bool checked)
{
    if(slotIsFocusItem() == 0) return;
        QTextCursor cursor = slotIsFocusItem()->textCursor();
        QTextCharFormat boldFormat;
        boldFormat.setFontWeight(checked ? QFont::Bold : QFont::Normal);
        cursor.mergeCharFormat(boldFormat);
        slotIsFocusItem()->setTextCursor(cursor);
}

void SectorGraphicsView::slotOnToolButton_Italic_2_clicked(bool checked)
{
    if(slotIsFocusItem() == 0) return;
    QTextCursor cursor = slotIsFocusItem()->textCursor();
    QTextCharFormat italicFormat;
    italicFormat.setFontItalic(checked);
    cursor.mergeCharFormat(italicFormat);
    slotIsFocusItem()->setTextCursor(cursor);
}

void SectorGraphicsView::slotOnToolButton_Underline_2_clicked(bool checked)
{
    if(slotIsFocusItem() == 0) return;
    QTextCursor cursor = slotIsFocusItem()->textCursor();
    QTextCharFormat underlineFormat;
    underlineFormat.setFontUnderline(checked);
    cursor.mergeCharFormat(underlineFormat);
    slotIsFocusItem()->setTextCursor(cursor);
}

void SectorGraphicsView::slotOnToolButton_color_2_clicked()
{
    if(slotIsFocusItem() == 0) return;
    QTextCursor cursor = slotIsFocusItem()->textCursor();
    QTextCharFormat foregroundFormat;
    foregroundFormat.setForeground(QBrush(qvariant_cast<QColor>(ui->toolButton_color_2->menu()
                                                                ->defaultAction()->data())));
    cursor.select(QTextCursor::Document);
    cursor.mergeCharFormat(foregroundFormat);
    slotIsFocusItem()->setTextCursor(cursor);



    slotIsFocusItem()->setDefaultTextColor(qvariant_cast<QColor>(
                                        ui->toolButton_color_2->menu()->defaultAction()->data()));
    // Послкольку мы не знаем какой итем получил цвет, то обращаемся к data. Хотя можно было objectName...
    vecAll_Item_LineD[slotIsFocusItem()->data(1).toInt()]->setDefaultTextColor(qvariant_cast<QColor>(
                                                 ui->toolButton_color_2->menu()->defaultAction()->data()));

}

