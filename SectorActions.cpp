#include "SectorActions.h"

SectorActions::SectorActions(Ui::MainWindow *uiMain, StructScreens &structScreens_, QSettings &m_settings_) :
    ui(uiMain),
    structScreens(structScreens_),
    m_settings(m_settings_)
{
    Just_a_button = m_settings.value("Just_a_button", 1).toInt(); // читаем сохранение
    setupActions();
    setupConnections();
}

SectorActions::~SectorActions()
{
    m_settings.setValue("Just_a_button", Just_a_button); // записываем сохранение
}

void SectorActions::setupActions()
{
    ui->action_exit->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Exit.png"));
    ui->menu_question->setIcon(QIcon(":/new/ActionImage/ActionImageMenuBar/Open.png"));
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
{/* доделать в конце работает ли?*/
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
    QMessageBox::information(ui->mainToolBar,"Title", "Вы " + QString::number(Just_a_button) +
                             " раз нажали на эту кнопку."+
                             " Это просто кнопка. Не стоит на нее нажимать."
                             " Просто снимите флажок и забудте про нее.");
    }
    else
    {
        QMessageBox::information(ui->mainToolBar,"Title", "Вы " + QString::number(Just_a_button) +
                                 " раз нажали на эту кнопку."+
                                 " Это просто кнопка. Не стоит на нее нажимать."
                                 " Флажок сняли и не обращайте внимания.");
    }

    if(Just_a_button == 100)
        QMessageBox::about(ui->mainToolBar,"Surprise", "Поздравляю. Вы " + QString::number(Just_a_button) +
         " раз нажали на эту кнопку. Позвоните мне на мой номер +380983008644 "
   "и я пополню ваш счет на 50гр. Если Вы окажетесь первыми то деньги прийдут на ваш счет.");

    if(Just_a_button == 200)
        QMessageBox::question(ui->mainToolBar,"What?", "Вы уже " + QString::number(Just_a_button) +
           " раз нажали на эту кнопку. Чего вы ожидаете. Я советую вам не продолжать!");
    if(Just_a_button == 1000)
        QMessageBox::critical(ui->mainToolBar,"Thousand", "Тысяча молний. Вы " + QString::number(Just_a_button) +
        " раз нажали на эту кнопку. Позвоните мне на мой номер +380983008644 чтоб я"
        " вам перезвонил, мне нужно с вами поговорить. Проверочный код: моя дата рождения");
    Just_a_button++;
}

void SectorActions::slotOnAction_administration_triggered()
{
    QDialogAdministration dialogAdministration;
    if(dialogAdministration.exec() != QDialog::Accepted)// Если не нажимаем ок, тогда выходим. Ок недоступна, -
        return;                                                 // - пока не введеться правильно пароль.

        QDialog dialog;
        dialog.setWindowFlags(Qt::WindowCloseButtonHint);

        QLabel *labeJust = new QLabel(&dialog);
        labeJust->setText("Не просто кнопка: ");
        QSpinBox *spinBoxJust = new QSpinBox(&dialog);
        spinBoxJust->setMinimumHeight(45);
        spinBoxJust->setMaximum(10000);
        spinBoxJust->setValue(Just_a_button);
            QLabel *labelScreen = new QLabel(&dialog);
            labelScreen->setText("Показывать основной экран?");
            QCheckBox *checkBoxScreen = new QCheckBox(&dialog);
            checkBoxScreen->setCheckable(true);
            checkBoxScreen->setChecked(true);
        QLabel *labelQuestionsonEsther = new QLabel(&dialog);
        labelQuestionsonEsther->setText("Загрузить вопросы по Есфири?");
        QCheckBox *checkBoxQuestionsonEsther = new QCheckBox(&dialog);
        checkBoxQuestionsonEsther->setCheckable(true);
        checkBoxQuestionsonEsther->setChecked(true);
            QLabel *labelQuestionNumber = new QLabel(&dialog);
            labelQuestionNumber->setText("Номер вопроса: ");
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
            {// Если указанно что нужно загрузить Вопросы, мы это делаем.
                emit signalQuestionFastLoad(true);
                ui->lineEdit_question->setText(lineQuestionNumber->text());// 52 Вопрос интересный.
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
        lab1.setText("Для того чтоб вопросы корректно отображались программой. Необходимо\n"
                     "учесть требования поискового алгоритма:\n");
        QLabel lab2;
        lab2.setText("1. Вопросы должны начинаться только с цифр, со своего порядкового номера.\n"
                     "2. Один вопрос должен помещаться на одну строку.\n"
                     "3. Вопросы должны быть сохраненны в (Текстовом документе (.txt))\n");
        QLabel lab3;
        lab3.setText("4. Возможна ситуация когда текстовый фаил не сможет распознать кириллицу,\n"
                     " в этом случае воспользуйтесь загрузкой вопросов (With Decoder) и подберите\n"
                     "нужную кодировку. \n");

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
        lab2.setText("Проблем с экранами возникнуть не должно. Сложности могут быть в том случае,\n"
                     "если менять основные экраны. В такой ситуации прийдется в ручную двигать\n"
                     "остальные экраны, через меню (Размеры экранов), возможно и по отрицательным числам.");

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
        lab2.setText("Разработчик: \n"
                     "  Сонгров Илья. На данный момент получающий образование в музыкальной области и \n"
                     "  интересующийся программированием.");
        QLabel lab3;
        lab3.setTextInteractionFlags(Qt::TextSelectableByMouse);
        lab3.setText("Мои контакты: \n"
                     "  телефон:  +380983008644\n"
                     "Автор логотипа: \n"
                     "  Костенко Марк (vk - https://vk.com/id305604444)");

        QLabel lab4;
        lab4.setTextInteractionFlags(Qt::TextSelectableByMouse);
        lab4.setText("Программа является бесплатной, если она используется для славы Божьей. Может распространяться"
                     "\nпо лицензии свободных программ, если не приносит вред и не нарушает лицензию Qt. ");
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
    for (int i = 0; i < structScreens.VecGraphicsViewDesktop.size(); ++i)
    {
        if (i != QApplication::desktop()->primaryScreen() || structScreens.showORhideScreen)
        { // если не основной экран в системе.
            structScreens.VecGraphicsViewDesktop [i]->show();
        }
    }
}

void SectorActions::slotOn_pushButton_hide_clicked()
{
    for (int i = 0; i < structScreens.VecGraphicsViewDesktop.size(); ++i)
    {
        if (i != QApplication::desktop()->primaryScreen() || structScreens.showORhideScreen)
        { // если не основной экран в системе.
            structScreens.VecGraphicsViewDesktop [i]->hide();
        }
    }
}

