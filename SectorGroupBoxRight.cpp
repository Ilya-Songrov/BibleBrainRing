#include "SectorGroupBoxRight.h"

SectorGroupBoxRight::SectorGroupBoxRight(Ui::MainWindow *uiMain) :
    ui(uiMain)
{
    setupGroupBoxRight_png();
    setupActionsAndConnections();
}

void SectorGroupBoxRight::setupGroupBoxRight_png()
{
    vecPixImage.push_back(QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/Gradient 1.png"));
    vecPixImage.push_back(QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/Gradient 2.png"));
    vecPixImage.push_back(QPixmap(":/new/GroupBoxes/MaterialsGroupBoxes/chomu-potribno-beregty-pryrodu.jpg"));

        QPalette pal2 = ui->listWidget_pix->palette();
        pal2.setColor(QPalette::Text, QColor(206,190,255).darker(199));
        pal2.setColor(QPalette::Active, QPalette::Base, QColor(216,244,255).lighter(81));
        pal2.setColor(QPalette::Inactive, QPalette::Base, QColor(216,244,255).lighter(81));
        ui->listWidget_pix->setPalette(pal2);

    ui->listWidget_pix->setIconSize(QSize(48, 48));

    QListWidgetItem* pitem = 0;

        pitem = new QListWidgetItem("Градієнт 1.png", ui->listWidget_pix);
            pitem->setIcon(vecPixImage[0].scaled(QSize(48, 48),Qt::IgnoreAspectRatio));

        pitem = new QListWidgetItem("Градієнт 2.png", ui->listWidget_pix);
            pitem->setIcon(vecPixImage[1].scaled(QSize(48, 48),Qt::IgnoreAspectRatio));

        pitem = new QListWidgetItem("Поле.jpg", ui->listWidget_pix);
            pitem->setIcon(vecPixImage[2].scaled(QSize(48, 48),Qt::IgnoreAspectRatio));

            ui->listWidget_pix->setCurrentItem(pitem);
}

void SectorGroupBoxRight::setupActionsAndConnections()
{
    contextMenuPix = new QMenu(ui->menu); /* доделать в конце подыскать родителя*/
    contextMenuPix->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Delete1.png"),"Видалити");
    contextMenuPix->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/DeleteAll.png"),"Видалити все");
    contextMenuPix->addAction(QIcon(":/new/ActionImage/ActionImageMenuBar/Load.png"),"Завантажити");
    connect(contextMenuPix,SIGNAL(triggered(QAction*)),SLOT(slotActivatedPng(QAction*)));
    connect(ui->listWidget_pix, &MyQListWidget::signalDropListWidgetPix, this, &SectorGroupBoxRight::slotDropPix);


    connect(ui->listWidget_pix, &MyQListWidget::itemActivated, this,
            &SectorGroupBoxRight::slotOnListWidget_pix_itemActivated);
    connect(ui->listWidget_pix, &MyQListWidget::itemPressed, this,
            &SectorGroupBoxRight::slotOnListWidget_pix_itemPressed);
    connect(ui->listWidget_pix, &MyQListWidget::customContextMenuRequested, this,
            &SectorGroupBoxRight::slotExecContextMenuPng);

    connect(ui->pushButton_png, &QPushButton::clicked, this, &SectorGroupBoxRight::slotOnPushButton_png_clicked);
    connect(ui->radioButton_png, &QPushButton::clicked, this, &SectorGroupBoxRight::slotOnRadioButton_png_clicked);
    connect(ui->radioButton_2, &QPushButton::clicked, this, &SectorGroupBoxRight::slotOnRadioButton_2_clicked);
}

void SectorGroupBoxRight::slotExecContextMenuPng(const QPoint &)
{
    contextMenuPix->exec(QCursor::pos());
}

void SectorGroupBoxRight::slotActivatedPng(QAction* pAction)
{
    if(pAction->text() == "Видалити"){
        if(vecPixImage.size() != 0){
        vecPixImage.remove(ui->listWidget_pix->currentRow());
        QListWidgetItem *it = ui->listWidget_pix->item(ui->listWidget_pix->currentRow());
            delete it;
        }
    }
    if(pAction->text() == "Видалити все"){
        for (int var = 0; var < vecPixImage.size(); ++var){
            QListWidgetItem *it = ui->listWidget_pix->item(ui->listWidget_pix->currentRow());
            delete it;
        }
        vecPixImage.clear();
    }
    if(pAction->text() == "Завантажити"){
        slotOnPushButton_png_clicked();
    }
}



void SectorGroupBoxRight::slotDropPix(QString strPathDrop, QString objectNameN)
{
    QStringList listDrop;
    listDrop = strPathDrop.split(QLatin1Char('\n'),QString :: SkipEmptyParts);

    if(objectNameN == "listWidget_pix")// Если это музыка и listWidget котрый справа.
    {
        for (int var = 0; var < listDrop.size(); ++var)
        {
            vecPixImage.push_back(QPixmap(listDrop[var]));

            QListWidgetItem* pitem = 0;
            pitem = new QListWidgetItem(QDir(listDrop[var]).dirName(), ui->listWidget_pix);
            pitem->setIcon(vecPixImage[vecPixImage.size()-1].scaled(QSize(48, 48),Qt::IgnoreAspectRatio));
            ui->listWidget_pix->setCurrentItem(pitem);

           if(ui->radioButton_png->isChecked() && vecPixImage.size() != 0){
               QPixmap pixCurentForBrushScene = vecPixImage[ui->listWidget_pix->currentRow()].scaled(
                           QSize(400,300),Qt::IgnoreAspectRatio);
               emit signalSetBackgroundBrush(pixCurentForBrushScene);
           }
        }
    }
}

void SectorGroupBoxRight::slotOnPushButton_png_clicked()
{
    QString strFilter;
    QString str = QFileDialog::getOpenFileName(0,tr("Open Pixmap"), QDir::currentPath(),
            "Images (*.png *.jpg *.jpeg)"
            ";;  *.jpg", &strFilter);

    if (!str.isEmpty())
    {
        vecPixImage.push_back(QPixmap(str));

        QListWidgetItem* pitem = 0;
        pitem = new QListWidgetItem(QDir(str).dirName(), ui->listWidget_pix);
        pitem->setIcon(vecPixImage[vecPixImage.size()-1].scaled(QSize(48, 48),Qt::IgnoreAspectRatio));
        ui->listWidget_pix->setCurrentItem(pitem);

       if(ui->radioButton_png->isChecked() && vecPixImage.size() != 0)
       {
           QPixmap pixCurentForBrushScene = vecPixImage[ui->listWidget_pix->currentRow()].scaled(
                       QSize(400,300),Qt::IgnoreAspectRatio);
           emit signalSetBackgroundBrush(pixCurentForBrushScene);
       }
    }
}

void SectorGroupBoxRight::slotOnRadioButton_png_clicked(bool checked)
{
    if(checked && vecPixImage.size() != 0){
      QPixmap pixCurentForBrushScene = vecPixImage[ui->listWidget_pix->currentRow()].scaled(
                  QSize(400,300),Qt::IgnoreAspectRatio);
      emit signalSetBackgroundBrush(pixCurentForBrushScene);
    }
}

void SectorGroupBoxRight::slotOnRadioButton_2_clicked(bool checked_2)
{
    if(checked_2 == true){
        QPixmap pixCurentForBrushScene;
        emit signalSetBackgroundBrush(pixCurentForBrushScene);
    }
}

void SectorGroupBoxRight::slotOnListWidget_pix_itemActivated(QListWidgetItem *)
{
    ui->radioButton_png->setChecked(true);
    if(ui->radioButton_png->isChecked() && vecPixImage.size() != 0){
        QPixmap pixCurentForBrushScene = vecPixImage[ui->listWidget_pix->currentRow()].scaled(
                    QSize(400,300),Qt::IgnoreAspectRatio);
        emit signalSetBackgroundBrush(pixCurentForBrushScene);
    }
}

void SectorGroupBoxRight::slotOnListWidget_pix_itemPressed(QListWidgetItem *item)
{
    Q_UNUSED(item);
    if(ui->radioButton_png->isChecked() && vecPixImage.size() != 0)
    {
        QPixmap pixCurentForBrushScene = vecPixImage[ui->listWidget_pix->currentRow()].scaled(
                    QSize(400,300),Qt::IgnoreAspectRatio);
        emit signalSetBackgroundBrush(pixCurentForBrushScene);
    }
}
