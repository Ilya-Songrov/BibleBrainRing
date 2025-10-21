#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "QuestionSearch.h"
#include "SectorActions.h"
#include "SectorGraphicsView.h"
#include "SectorGroupBoxRight.h"
#include "SectorGroupBoxLeft.h"
#include "SectorPlayerAndTimer.h"
#include "StructScreens.h"

#include <QMainWindow>
#include <QtWidgets>
#include <QMediaPlayer>
#include <QMessageBox>
#include <QSettings>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QDebug>
#include <QWidget>
#include <QToolButton>
#include <QComboBox>
#include <QLineEdit>
#include <QColorDialog>
#include <QFontDialog>
#include <QFileDialog>
#include <QToolBar>
#include <QEvent>
#include <QMenu>
#include <QPixmap>

QT_BEGIN_NAMESPACE
class SectorActions;
class SectorGraphicsView;
QT_END_NAMESPACE


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void keyPressEvent(QKeyEvent* pe);

    QVector <QString> vecStrMusic;

    QSettings m_settings;
    StructScreens structScreens;

    SectorActions *sectorActions;
    SectorGroupBoxRight *sectorGroupBoxRight;
    SectorGroupBoxLeft *sectorGroupBoxLeft;
    SectorPlayerAndTimer *sectorPlayerAndTimer;
    SectorGraphicsView *sectorGraphicsView;
    QuestionSearch *questionSearch;

private:
    void setupConnections();
    void setupFront();

public:
    void ffShowPopupComboBox(){ ui->fontSizeCombo_2->showPopup(); }
    void ffHidePopupComboBox(){ ui->fontSizeCombo_2->hidePopup(); }

private:
    Ui::MainWindow *ui;
};


#endif // MAINWINDOW_H
