#include "QDialogAdministration.h"

QDialogAdministration::QDialogAdministration(QWidget *parent) : QDialog(parent)
{
    setupBody();
    fillVectorTry();
}

void QDialogAdministration::setupBody()
{
    gridLayout = new QGridLayout(this);
    lineEdit = new QLineEdit(this);
    label = new QLabel(this);
    label_2 = new QLabel(this);
    pushButton = new QPushButton("ок", this);
    pushButton_2 = new QPushButton("отмена", this);

        QFont font;
        font.setPointSize(10);
    this->setFont(font);
    this->resize(300, 133);
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
    label->setFont(font1);
    label->setTextFormat(Qt::RichText);
    label->setText("Введите пароль. Это секретные настройки.");
    pushButton->setEnabled(false);

    gridLayout->addWidget(label, 0, 0, 1, 2);
    gridLayout->addWidget(lineEdit, 1, 0, 1, 2);
    gridLayout->addWidget(label_2, 2, 0, 1, 2);
    gridLayout->addWidget(pushButton, 3, 0, 1, 1);
    gridLayout->addWidget(pushButton_2, 3, 1, 1, 1);
    this->setLayout(gridLayout);

    QObject::connect(pushButton, SIGNAL(clicked()), this, SLOT(accept()));
    QObject::connect(pushButton_2, SIGNAL(clicked()), this, SLOT(reject()));
    QObject::connect(lineEdit, SIGNAL(textChanged(QString)), this, SLOT(on_lineEdit_textChanged(QString)));
}

void QDialogAdministration::on_lineEdit_textChanged(const QString &arg1)
{
    if(arg1 == "20052017"){
        pushButton->setEnabled(true);
        label_2->setText("Осторожно!!!");
    }
    else{
        label_2->setText(vecTextTry[qrand() % (0 - 22)]);
    }
}

void QDialogAdministration::fillVectorTry()
{
    vecTextTry.push_back("Пытайся!");
    vecTextTry.push_back("Пытайся!");
    vecTextTry.push_back("Пытайся!");
    vecTextTry.push_back("Это связанно с датой летней встречи 2017");
    vecTextTry.push_back("По секрету. Букв нет");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("Пытайся!");
    vecTextTry.push_back("Может чет другое...");
    vecTextTry.push_back("Может чет другое...");
    vecTextTry.push_back("Здесь 8 цифр");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("А может буквы не стоит писать?");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("А может буквы не стоит писать?");
    vecTextTry.push_back("И кто вообще это придумал?");
    vecTextTry.push_back("Опа, опа... Лан шучу");
    vecTextTry.push_back("200520 - дальше уже додумай сам");
    vecTextTry.push_back("Пароль не сложный");
    vecTextTry.push_back("А может буквы не стоит писать?");
    vecTextTry.push_back("Пароль не сложный");
    vecTextTry.push_back("Опа, опа... Лан шучу");
    vecTextTry.push_back("Опа, опа... Лан шучу");
}
