#ifndef SECTORACTIONS_H
#define SECTORACTIONS_H

#include "ui_mainwindow.h"
#include "QDialogAdministration.h"
#include "StructScreens.h"

#include <QObject>
#include <QFileDialog>
#include <QColorDialog>
#include <QMessageBox>

class SectorActions : public QObject
{
    Q_OBJECT
public:
    SectorActions(Ui::MainWindow *uiMain, StructScreens &structScreens_, QSettings &m_settings_);
    ~SectorActions();

    Ui::MainWindow *ui;
    StructScreens &structScreens;
    QSettings &m_settings;

    int Just_a_button;

    void setupActions();
    void setupConnections();

public slots:
    void slotOn_checkBox_3_clicked(bool checked);
    void slotOnAction_save_triggeredSector();
    void slotOnAction_administration_triggered();
    void slotOnAction_Opening_questions_help_triggered();
    void slotOnAction_Screens_help_triggered();
    void slotOnAction_developer_triggered();
    void slotOnAction_AboutQt_triggered();
    void slotOn_pushButton_show_clicked();
    void slotOn_pushButton_hide_clicked();

signals:
    void signalQuestionFastLoad(bool boolQuestionsonEsther);

};

#endif // SECTORACTIONS_H
