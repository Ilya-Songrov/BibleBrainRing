#include "SectorActions.h"

SectorActions::SectorActions(Ui::MainWindow *uiMain, StructScreens &structScreens_, QSettings &m_settings_) :
    ui(uiMain),
    structScreens(structScreens_),
    m_settings(m_settings_)
{
    Just_a_button = m_settings.value("Just_a_button", 1).toInt(); // читаємо збереження
    setupActions();
    setupConnections();
}

SectorActions::~SectorActions()
{
    m_settings.setValue("Just_a_button", Just_a_button); // записуємо збереження
}

void SectorActions::setupActions()
{
    ui->action_exit->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Exit.png"));
    ui->action_question->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Open.png"));
    ui->action_question_fast->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Question.png"));
    ui->action_question_decocer->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Question5.png"));
    ui->action_save->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Save.png"));
    ui->action_Screens->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Screens.png"));

    ui->action_ItemLoadPixmap->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Load.png"));
    ui->action_ItemPixmapSize->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Size.png"));
    ui->action_Restore_by_default->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Restore.png"));
    ui->action_administration->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Admin.png"));

    ui->menu_help->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Note.png"));
    ui->action_Opening_questions_help->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Question.png"));
    ui->action_Screens_help->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Screens.png"));
    ui->action_developer->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/C++Developer.png"));
    ui->action_AboutQt->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Qt.png"));

}

void SectorActions::setupConnections()
{
    connect(ui->pushButton_show, &QPushButton::clicked, this, &SectorActions::slotOn_pushButton_show_clicked);
    connect(ui->pushButton_hide, &QPushButton::clicked, this, &SectorActions::slotOn_pushButton_hide_clicked);
    connect(ui->checkBox_3, &QCheckBox::clicked, this, &SectorActions::slotOn_checkBox_3_clicked);
}

void SectorActions::slotOnAction_save_triggeredSector()
{/* доробити в кінці чи працює?*/
    QString strFilter;
    QString str = QFileDialog::getSaveFileName(0,QObject::tr("Save Pixmap"),
        ui->lineEdit_1->text() + " - " + ui->lineEdit_2->text(),"*.jpg",&strFilter);

    if (!str.isEmpty())
    {
        QPixmap pixSaveResult;
        pixSaveResult = structScreens.VecGraphicsViewDesktop[0]->grab();
        pixSaveResult.save(str, "JPG");
    }
}

void SectorActions::slotOn_checkBox_3_clicked(bool checked)
{
    if(checked == true)
    {
    QMessageBox::information(ui->mainToolBar,"Title", "Ви " + QString::number(Just_a_button) +
                                                " разів натиснули на цю кнопку." +
                                                " Це просто кнопка. Не варто на неї натискати." +
                                                " Просто зніміть прапорець і забудьте про неї.");
    }
    else
    {
        QMessageBox::information(ui->mainToolBar,"Title", "Ви " + QString::number(Just_a_button) +
                                                            " разів натиснули на цю кнопку." +
                                                            " Це просто кнопка. Не варто на неї натискати." +
                                                            " Прапорець зняли і не звертайте на неї уваги.");
    }

    if(Just_a_button == 100)
        QMessageBox::about(ui->mainToolBar,"Surprise", "Вітаю. Ви " + QString::number(Just_a_button) +
                                                    " разів натиснули на цю кнопку. Напишіть мені в Instagram @ilya_songrov"
                                                    " і отримайте приз.");

    if(Just_a_button > 200)
        QMessageBox::question(ui->mainToolBar,"What?", "Ви вже " + QString::number(Just_a_button) +
                                                        " разів натиснули на цю кнопку. Чого ви очікуєте? Рекомендую вам не продовжувати!");
    Just_a_button++;
}

void SectorActions::slotOnAction_administration_triggered()
{
    QDialogAdministration dialogAdministration;
    if(dialogAdministration.exec() != QDialog::Accepted)// Якщо не натискаємо ок, тоді виходимо. Ок недоступна, -
        return;                                                 // - поки не введеться правильно пароль.

        QDialog dialog;
        dialog.setWindowFlags(Qt::WindowCloseButtonHint);

        QLabel *labeJust = new QLabel(&dialog);
        labeJust->setText("Не просто кнопка: ");
        QSpinBox *spinBoxJust = new QSpinBox(&dialog);
        spinBoxJust->setMinimumHeight(45);
        spinBoxJust->setMaximum(10000);
        spinBoxJust->setValue(Just_a_button);
            QLabel *labelScreen = new QLabel(&dialog);
            labelScreen->setText("Показати головний екран?");
            QCheckBox *checkBoxScreen = new QCheckBox(&dialog);
            checkBoxScreen->setCheckable(true);
            checkBoxScreen->setChecked(true);
        QLabel *labelQuestionsonEsther = new QLabel(&dialog);
        labelQuestionsonEsther->setText("Завантажити питання по Естер?");
        QCheckBox *checkBoxQuestionsonEsther = new QCheckBox(&dialog);
        checkBoxQuestionsonEsther->setCheckable(true);
        checkBoxQuestionsonEsther->setChecked(true);
            QLabel *labelQuestionNumber = new QLabel(&dialog);
            labelQuestionNumber->setText("Номер питання: ");
            QLineEdit *lineQuestionNumber = new QLineEdit(&dialog);
            lineQuestionNumber->setText("52");

        QPushButton *pushButton1 = new QPushButton(&dialog);
        pushButton1->setText("Ok");
        QPushButton *pushButton2 = new QPushButton(&dialog);
        pushButton2->setText("Cancel");

        QGridLayout gridLayout;
        gridLayout.addWidget(labeJust,0,0);
        gridLayout.addWidget(spinBoxJust,0,1);
            gridLayout.addWidget(labelScreen,1,0);
            gridLayout.addWidget(checkBoxScreen,1,1);
        gridLayout.addWidget(labelQuestionsonEsther,2,0);
        gridLayout.addWidget(checkBoxQuestionsonEsther,2,1);
            gridLayout.addWidget(labelQuestionNumber,3,0);
            gridLayout.addWidget(lineQuestionNumber,3,1);
        gridLayout.addWidget(pushButton1,4,0);
        gridLayout.addWidget(pushButton2,4,1);
        dialog.setLayout(&gridLayout);

        connect(pushButton1,SIGNAL(clicked()),&dialog,SLOT(accept()));
        connect(pushButton2,SIGNAL(clicked()),&dialog,SLOT(reject()));
        if(dialog.exec() == QDialog::Accepted)
        {
            Just_a_button = spinBoxJust->value();
            structScreens.showORhideScreen = checkBoxScreen->isChecked();
            if(checkBoxQuestionsonEsther->isChecked())
            {// Якщо вказано що потрібно завантажити Питання, ми це робимо.
                emit signalQuestionFastLoad(true);
                ui->lineEdit_question->setText(lineQuestionNumber->text());// 52 Питання цікаве.
                ui->lineEdit_question->setFocus();
            }
        }
}

void SectorActions::slotOnAction_Opening_questions_help_triggered()
{
    QDialog dialog;
    dialog.setWindowFlags(Qt::WindowCloseButtonHint);
    dialog.setEnabled(true);
    QScrollArea scr(&dialog);
    QWidget wgt(&dialog);

    QPalette palette;
    palette.setBrush(QPalette::Normal, QPalette::Background,QBrush(Qt::lightGray));
    dialog.setPalette(palette);

    QVBoxLayout vbox(&wgt);
    QVBoxLayout vbox2;
        QLabel lab1;
        lab1.setText("Щоб питання коректно відображались програмою, необхідно\n"
                     "врахувати вимоги пошукового алгоритму:\n");
        QLabel lab2;
        lab2.setText("1. Питання повинні починатися тільки з цифр, зі свого порядкового номера.\n"
                     "2. Одне питання повинно поміщатися на один рядок.\n"
                     "3. Питання повинні бути збережені в (Текстовому документі (.txt))\n");
        QLabel lab3;
        lab3.setText("4. Можлива ситуація, коли текстовий файл не зможе розпізнати кирилицю,\n"
                     "у цьому випадку скористайтесь завантаженням питань (With Decoder) та підберіть\n"
                     "потрібну кодування.\n");

        vbox.addWidget(&lab1);
        vbox.addWidget(&lab2);
        vbox.addWidget(&lab3);

        wgt.setLayout(&vbox);

        scr.setWidget(&wgt);
        vbox2.addWidget(&scr);

    dialog.setLayout(&vbox2);
    dialog.setFixedSize(500,304);
    dialog.exec();
}

void SectorActions::slotOnAction_Screens_help_triggered()
{
    QDialog dialog;
    dialog.setWindowFlags(Qt::WindowCloseButtonHint);
    dialog.setEnabled(true);
    QScrollArea scr(&dialog);
    QWidget wgt(&dialog);

    QPalette palette;
    palette.setBrush(QPalette::Normal, QPalette::Background,QBrush(Qt::lightGray));
    dialog.setPalette(palette);

    QVBoxLayout vbox(&wgt);
    QVBoxLayout vbox2;
        QLabel lab1;
        lab1.setPixmap(QPixmap(":/new/ActionImage/ActionImageMenuBar/Screens.png").
                       scaled(300,200,Qt::KeepAspectRatio));
        QLabel lab2;
        lab2.setText("Проблем з екранами виникнути не повинно. Складнощі можуть бути лише у випадку,\n"
                     "якщо змінювати основні екрани. У такій ситуації доведеться вручну пересувати\n"
                     "інші екрани через меню (Розміри екранів), можливо, і з використанням від’ємних чисел.");

        vbox.addWidget(&lab1);
        vbox.addWidget(&lab2);

        wgt.setLayout(&vbox);

        scr.setWidget(&wgt);
        vbox2.addWidget(&scr);

    dialog.setLayout(&vbox2);
    dialog.setFixedSize(510,304);
    dialog.exec();
}

void SectorActions::slotOnAction_developer_triggered()
{
    QDialog dialog;
    dialog.setWindowFlags(Qt::WindowCloseButtonHint);
    QScrollArea scr(&dialog);
    QWidget wgt(&dialog);

    QPalette palette;
    palette.setBrush(QPalette::Normal, QPalette::Background,QBrush(Qt::lightGray));
    dialog.setPalette(palette);

    QVBoxLayout vbox(&wgt);
    QVBoxLayout vbox2;
        QLabel lab1;
        lab1.setPixmap(QPixmap(":/new/Other/FilesAndLogo/Logo_temporarily.png"));
        QLabel lab2;
        lab2.setTextInteractionFlags(Qt::TextSelectableByMouse);
        lab2.setText("Версія: v3.0.1"); // version
        QLabel lab3;
        lab3.setTextInteractionFlags(Qt::TextSelectableByMouse);
        lab3.setText("Розробник: @ilya_songrov (Instagram)");
        QLabel lab4;
        lab4.setTextInteractionFlags(Qt::TextSelectableByMouse);
        lab4.setText("Програма є безкоштовною, якщо вона використовується для Слави Божої. Може поширюватися\n"
                     "за ліцензією вільного програмного забезпечення, якщо не завдає шкоди та не порушує ліцензію Qt.");
        vbox.addWidget(&lab1);
        vbox.addWidget(&lab2);
        vbox.addWidget(&lab3);
        vbox.addWidget(&lab4);

        wgt.setLayout(&vbox);

        scr.setWidget(&wgt);
        vbox2.addWidget(&scr);

    dialog.setLayout(&vbox2);
    dialog.setFixedSize(570,390);
    dialog.exec();
}

void SectorActions::slotOnAction_AboutQt_triggered()
{
    QMessageBox::aboutQt(structScreens.parentWidget,"AboutQt");
}

void SectorActions::slotOn_pushButton_show_clicked()
{

    if ((structScreens.VecGraphicsViewDesktop.size() < 2))
    {
        QMessageBox::information(ui->mainToolBar,"Title", "Не знайдено екранів. Під'єднайте кабель і перезапустіть додаток.");
        return;
    }
    
    for (int i = 0; i < structScreens.VecGraphicsViewDesktop.size(); ++i)
    {
        if (i != QApplication::desktop()->primaryScreen() || structScreens.showORhideScreen)
        { // якщо не основний екран в системі.
            structScreens.VecGraphicsViewDesktop [i]->show();
        }
    }
}

void SectorActions::slotOn_pushButton_hide_clicked()
{
    for (int i = 0; i < structScreens.VecGraphicsViewDesktop.size(); ++i)
    {
        if (i != QApplication::desktop()->primaryScreen() || structScreens.showORhideScreen)
        { // якщо не основний екран в системі.
            structScreens.VecGraphicsViewDesktop [i]->hide();
        }
    }
}

