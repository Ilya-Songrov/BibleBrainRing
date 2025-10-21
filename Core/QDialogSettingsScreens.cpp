#include "QDialogSettingsScreens.h"

QDialogSettingsScreens::QDialogSettingsScreens(StructScreens &structScreens_, QWidget *parent) :
    QDialog(parent), // Для запам'ятовування, ініціалізація батька повинна бути раніше ініціалізації полів.
    structScreens(structScreens_)
{
    setupBudy();
    setupTableWidget();

    connect(pushButton_reset, &QPushButton::clicked, this, &QDialogSettingsScreens::slotOnPushButton_reset_clicked);
    connect(pushButton_ok, &QPushButton::clicked, this, &QDialogSettingsScreens::slotOnPushButton_ok_clicked);
    connect(pushButton_cancel, &QPushButton::clicked, this, &QDialogSettingsScreens::reject);
    connect(pushButton_apply, &QPushButton::clicked, this, &QDialogSettingsScreens::slotOnPushButton_apply_clicked);
}

void QDialogSettingsScreens::setupBudy()
{
    setWindowFlags(Qt::WindowCloseButtonHint);
    this->resize(543,275);

    gridLayout = new QGridLayout(this);
    tableWidget = new QTableWidget(this);

    gridLayout->addWidget(tableWidget, 1, 0, 1, 1);

    label = new QLabel(this);
    QFont font;
    font.setPointSize(10);
    font.setBold(true);
    font.setUnderline(false);
    font.setWeight(75);
    label->setFont(font);
    label->setTextFormat(Qt::AutoText);
    label->setText("Думайте, перш ніж щось змінювати!");

    gridLayout->addWidget(label, 0, 0, 1, 1);

    horizontalLayout = new QHBoxLayout;
    pushButton_reset = new QPushButton("Скинути", this);
    pushButton_reset->setMinimumSize(QSize(0, 26));

    horizontalLayout->addWidget(pushButton_reset);

    horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    horizontalLayout->addItem(horizontalSpacer);

    pushButton_ok = new QPushButton("Ок", this);
    pushButton_ok->setMinimumSize(QSize(0, 26));

    horizontalLayout->addWidget(pushButton_ok);

    pushButton_cancel = new QPushButton("Відміна", this);
    pushButton_cancel->setMinimumSize(QSize(0, 26));

    horizontalLayout->addWidget(pushButton_cancel);

    pushButton_apply = new QPushButton("Застосувати", this);
    pushButton_apply->setMinimumSize(QSize(0, 26));

    horizontalLayout->addWidget(pushButton_apply);


    gridLayout->addLayout(horizontalLayout, 2, 0, 1, 1);

    QWidget::setTabOrder(tableWidget, pushButton_apply);
    QWidget::setTabOrder(pushButton_apply, pushButton_ok);
    QWidget::setTabOrder(pushButton_ok, pushButton_cancel);
    QWidget::setTabOrder(pushButton_cancel, pushButton_reset);

    QObject::connect(pushButton_cancel, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(pushButton_ok, SIGNAL(clicked()), this, SLOT(accept()));

}

void QDialogSettingsScreens::setupTableWidget()
{
    desktopWidgetDialog = QApplication::desktop();

    countScreen = structScreens.VecGraphicsViewDesktop.size();
    tableWidget->setRowCount(countScreen);
    tableWidget->setColumnCount(4);
    QTableWidgetItem* ptwi = 0;
    QStringList lstHorizontal;
    lstHorizontal << "Ширина" << "Висота" << "Рухатись по X" << "Рухатись по Y";
    tableWidget->setHorizontalHeaderLabels(lstHorizontal);
    QStringList lstVertical;
    for (int i = 0; i < countScreen; ++i)
    {
        if (i != desktopWidgetDialog->primaryScreen())
        {lstVertical << "Екран " + QString::number(i);}
        else
        {lstVertical << "Екран головний";}
        tableWidget->setVerticalHeaderLabels(lstVertical);

        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewDesktop[i]->width()-6));
        tableWidget->setItem(i, 0, ptwi);
        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewDesktop[i]->height()-6));
        tableWidget->setItem(i, 1, ptwi);
        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewDesktop[i]->x()));
        tableWidget->setItem(i, 2, ptwi);
        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewDesktop[i]->y()));
        tableWidget->setItem(i, 3, ptwi);
    }
}


void QDialogSettingsScreens::slotOnPushButton_apply_clicked()
{
    int row = tableWidget->rowCount();
    for (int var = 0; var < row; ++var)
    { // for для обходу всіх екранів в системі. Щоб для кожного окремо підготувати GraphicsView
      // додавання цифр (+6,-3) для того щоб не були видні краї екрана, вони за замовчуванням білі.
      // на чорному тлі це прекрасно помітно.

        int intDesWidth = tableWidget->item(var,0)->text().toInt()+6;
        int intDesHeight = tableWidget->item(var,1)->text().toInt()+6;
        int intDesMove_X = tableWidget->item(var,2)->text().toInt();
        int intDesMove_Y = tableWidget->item(var,3)->text().toInt();


        structScreens.VecGraphicsViewDesktop[var]->scale(1 / structScreens.VecGraphicsViewScaleSize[var].width(),
                                           1 / structScreens.VecGraphicsViewScaleSize[var].height());
        structScreens.VecGraphicsViewScaleSize[var] = QSizeF((qreal)intDesWidth / 400,(qreal)intDesHeight / 300);
        structScreens.VecGraphicsViewDesktop[var]->scale(structScreens.VecGraphicsViewScaleSize[var].width(),
                                           structScreens.VecGraphicsViewScaleSize[var].height());
        structScreens.VecGraphicsViewDesktop[var]->setMinimumSize(intDesWidth,intDesHeight);
        structScreens.VecGraphicsViewDesktop[var]->resize(intDesWidth,intDesHeight);
        structScreens.VecGraphicsViewDesktop[var]->move(intDesMove_X,intDesMove_Y);
    }
}

void QDialogSettingsScreens::slotOnPushButton_ok_clicked()
{
    slotOnPushButton_apply_clicked();
}

void QDialogSettingsScreens::slotOnPushButton_reset_clicked()
{

    QTableWidgetItem* ptwi = 0;
    QStringList lstHorizontal;
    lstHorizontal << "Ширина" << "Висота" << "Рухатись по X" << "Рухатись по Y";
    tableWidget->setHorizontalHeaderLabels(lstHorizontal);
    QStringList lstVertical;
    for (int i = 0; i < countScreen; ++i)
    {
        if (i != desktopWidgetDialog->primaryScreen())
        {lstVertical << "Екран "+QString::number(i);}
        else
        {lstVertical << "Екран головний";}
        tableWidget->setVerticalHeaderLabels(lstVertical);

        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewReset[i] [0] - 6));
        tableWidget->setItem(i, 0, ptwi);
        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewReset[i] [1] - 6));
        tableWidget->setItem(i, 1, ptwi);
        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewReset[i] [2]));
        tableWidget->setItem(i, 2, ptwi);
        ptwi = new QTableWidgetItem(QString::number(structScreens.VecGraphicsViewReset[i] [3]));
        tableWidget->setItem(i, 3, ptwi);
    }
}

