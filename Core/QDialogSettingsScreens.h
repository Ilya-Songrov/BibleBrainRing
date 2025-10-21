#ifndef QDIALOGSETTINGSSCREENS_H
#define QDIALOGSETTINGSSCREENS_H

#include "QDialog"
#include "QVector"
#include "QtWidgets"
#include "StructScreens.h"

class QDialogSettingsScreens : public QDialog
{
    Q_OBJECT
public:
    QDialogSettingsScreens(StructScreens &structScreens_, QWidget *parent = 0);

    StructScreens &structScreens;
    QTableWidget *tableWidget;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_reset;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_ok;
    QPushButton *pushButton_cancel;
    QPushButton *pushButton_apply;
    QGridLayout *gridLayout;


    QDesktopWidget *desktopWidgetDialog;
    int countScreen;

    void setupBudy();
    void setupTableWidget();

private slots:
    void slotOnPushButton_apply_clicked();

    void slotOnPushButton_ok_clicked();

    void slotOnPushButton_reset_clicked();

};

#endif // QDIALOGSETTINGSSCREENS_H
