#ifndef SECTORGROUPBOXERIGHT_H
#define SECTORGROUPBOXERIGHT_H

#include "MyQListWidget.h"
#include "ui_mainwindow.h"

#include <QObject>
#include <QDir>
#include <QFileDialog>

class SectorGroupBoxeRight : public QObject
{
    Q_OBJECT
public:
    SectorGroupBoxeRight(Ui::MainWindow *uiMain);

private:
    Ui::MainWindow *ui;
    QVector <QPixmap> vecPixImage;
    QMenu *contextMenuPix;

    void setupGroupBoxRight_png();
    void setupActionsAndConnections();

private slots:
    void slotDropPix(QString strPathDrop, QString objectNameN);

public slots:
    void slotActivatedPng(QAction* pAction);
    void slotOnPushButton_png_clicked();
    void slotOnRadioButton_png_clicked(bool checked);
    void slotOnRadioButton_2_clicked(bool checked_2);
    void slotOnListWidget_pix_itemActivated(QListWidgetItem *);
    void slotOnListWidget_pix_itemPressed(QListWidgetItem *item);
    void slotExecContextMenuPng(const QPoint &);

signals:
    void signalSetBackgroundBrush(QPixmap pixCurent);

};

#endif // SECTORGROUPBOXERIGHT_H
