#ifndef SECTORGRAPHICSVIEW_H
#define SECTORGRAPHICSVIEW_H

#include "ui_mainwindow.h"
#include "myQGraphicsTextItem.h"
#include "QDialogSettingsScreens.h"
#include "StructScreens.h"

#include "QObject"
#include "QtWidgets"
#include "QVector"
#include "QGraphicsScene"
#include "QGraphicsTextItem"
#include "QColorDialog"

QT_BEGIN_NAMESPACE
class myQGraphicsTextItem;
QT_END_NAMESPACE


class SectorGraphicsView : public QObject
{// Здесь обрабатываются сцена и виджеты над сценой
    Q_OBJECT
public:
    SectorGraphicsView(Ui::MainWindow *uiMain, int timerBasic, StructScreens &structScreens_,
                                                            QSettings &m_settings_);
    ~SectorGraphicsView();

    Ui::MainWindow *ui;
    int int_timer_basic;
    StructScreens &structScreens;
    QSettings &m_settings;

    QGraphicsScene main_scene;
    QGraphicsScene sceneD;
    QColor color_backgroundScene_Dialog;


    QGraphicsPixmapItem *Item_LineTitlePixmap; // заглавие картинка

    QTextDocument *Doc_LineTitleText;
        myQGraphicsTextItem *Item_LineTitleText; // заглавие текст
    QTextDocument *Doc_LineFirstTeam;
        myQGraphicsTextItem *Item_LineFirstTeam;
    QTextDocument *Doc_LineSecondTeam;
        myQGraphicsTextItem *Item_LineSecondTeam;
    QTextDocument *Doc_LineFirstPoints;
        myQGraphicsTextItem *Item_LineFirstPoints;
    QTextDocument *Doc_LineSecondPoints;
        myQGraphicsTextItem *Item_LineSecondPoints;
    QTextDocument *Doc_LineQuestion;
        myQGraphicsTextItem *Item_LineQuestion;
    QTextDocument *Doc_LineTimer;
        myQGraphicsTextItem *Item_LineTimer;


    // сначала думал без вектора обойдусь, но после пришлось сделать, когда уже почти все сделал. Смешно просто.
    QVector <myQGraphicsTextItem *> vecAll_Item_Line;
    QVector <myQGraphicsTextItem *> vecAll_Item_LineD; // еще и этот вектор понадобился
    int intIntervalPlusMinus = 0;


    // другие экраны:
    QGraphicsPixmapItem *Item_LineTitlePixmapD; // заглавие картинка
    myQGraphicsTextItem *Item_LineTitleTextD; // заглавие текст
    myQGraphicsTextItem *Item_LineFirstTeamD;
    myQGraphicsTextItem *Item_LineSecondTeamD;
    myQGraphicsTextItem *Item_LineFirstPointsD;
    myQGraphicsTextItem *Item_LineSecondPointsD;
    myQGraphicsTextItem *Item_LineQuestionD;
    myQGraphicsTextItem *Item_LineTimerD;

    QMenu *sceneMenu;
    QMenu *sceneMenuAllitem;
        QAction *aFontAllitem;
        QAction *aColorAllitem;
        QAction *aBackgroundAllitem;
        QAction *aRectAllitem;
        QAction *aAutoFontQuestion;
        QAction *aAutoZeroPoints;
    QMenu *sceneMenuUseItem;
        QAction *aRemuveTitlePixmapItem;
        QAction *aRemuveTitleTextItem;
        QAction *aRemuveTeam1item;
        QAction *aRemuveTeam2item;
        QAction *aRemuvePoints1item;
        QAction *aRemuvePoints2item;
        QAction *aRemuveQuestionitem;
        QAction *aRemuveTimeritem;
        QAction *aNothingNotUse;
    QMenu *sceneMenuTimer;
        QAction *aTimerTime;
        QAction *aTimerSpeed;
        QAction *aTimerComeback;
        QAction *aTimerNegativeNumbers;
        QAction *aTimerGradient;

        bool boolFontDefaultItemsReset = false;// При первом запуске прочтение сохранения установить здесь истину,
        // что позволит использовать дефолтный шрифт. При повторных запусках будут использоваться сохраненные
        // настройки, поскольку дефолт будет установлен на ложь. При сбросе настроек опять установиться истина.

        QColor colorItem_LineTitle;
        QColor colorItem_LineFirstTeam;
        QColor colorItem_LineSecondTeam;
        QColor colorItem_LineFirstPoints;
        QColor colorItem_LineSecondPoints;
        QColor colorItem_LineQuestion;
        QColor colorItem_LineTimer;

        QString strItem_LineTitle = "<CENTER><b>Задать трудный вопрос легко!</b> <br> <i>Уистен Хью Оден</i></CENTER>";
        QString strItem_LineFirstTeam = "<CENTER>Килия</CENTER>";
        QString strItem_LineSecondTeam = "<CENTER>Одесса</CENTER>";
        QString strItem_LineFirstPoints = "<CENTER>43</CENTER>";
        QString strItem_LineSecondPoints = "<CENTER>2</CENTER>";

        QPixmap pixLineTitlePixmap;
        QPixmap pixCurentForBrushScene; // фон сцены


        void readSettingsSectorGraphicsView();
        void writeSettingsSectorGraphicsView();
private slots: /* доделать в конце  public? */
    void setupEverythingThatAreAboveStage();
    void setupAndCreateMainScene();
    void setupAndCreateSceneSecond();
    void setupPushButton_color();
    void writeTextChanged_on_Item_Line(myQGraphicsTextItem *Item, const int pos, const QString &str);


    QPixmap createColorToolButtonIcon(QColor color);
    QMenu *createColorMenu(QColor defaultColor);
    void textColorChanged();
    void ffRefresh_ItemPos();
        void refreshPosOtherScreens();/* доделать в конце move to private*/
        void slotRefresh_ItemPos();
        void slotRefresh_Tool();
        myQGraphicsTextItem *slotIsFocusItem();
        void slotfocusItemChanged(QGraphicsItem *newFocus, QGraphicsItem *oldFocus, Qt::FocusReason reason);
        void slotSetFont();
        void slot_fontSizeCombo_highlighted_AND_activated(int index);
        void slotLineTextChanged(const QString str);
        void slotSceneMenuExec(const QPoint &pos);
        void slotActionMenuTriggered(bool);
        void slotSceneMenuTriggered(QAction *action);
        void slotQuestion(const QString &str);

public slots:
    void slotOnToolButton_plus_2_clicked();
    void slotOnToolButton_minus_2_clicked();
    void slotOnToolButton_Bold_2_clicked(bool checked);
    void slotOnToolButton_Italic_2_clicked(bool checked);
    void slotOnToolButton_Underline_2_clicked(bool checked);
    void slotOnToolButton_color_2_clicked();

public slots:
    void slotWriteTextChanged_on_TimerItem(int int_SecondsTimer_changing_now, QString strTimer);
    void slotQuestionPublic(QString str){ slotQuestion(str); }
    void slotSetLoadPixmap();
    void slotSetItemPixmapSize();
    void slotSettingsScreens();
    void slotSetBackgroundBrush(QPixmap pixCurent);
    void slotOnPushButton_color_clicked();
    void slotOnCheckBox_timer_clicked(bool checked);


signals:
    void aColorToPushButtonColorClicked();
    void aTimeToActionSceneMenuTimerTimeTriggered();
    void aSpeedToActionSceneMenuTimerSpeedTriggered();

};

#endif // QGRAPHICSVIEWANDALL_H
