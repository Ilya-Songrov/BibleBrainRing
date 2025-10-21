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
    pushButton = new QPushButton("Гаразд", this);
    pushButton_2 = new QPushButton("Скасувати", this);

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
    label->setText("Введіть пароль. Це секретні налаштування.");
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
    vecTextTry.push_back("Пробуй!");
    vecTextTry.push_back("Пробуй!");
    vecTextTry.push_back("Пробуй!");
    vecTextTry.push_back("Це пов’язано з датою літньої зустрічі 2017");
    vecTextTry.push_back("По секрету: літер немає");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("Пробуй!");
    vecTextTry.push_back("Може, щось інше...");
    vecTextTry.push_back("Може, щось інше...");
    vecTextTry.push_back("Тут 8 цифр");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("А може, літери не варто писати?");
    vecTextTry.push_back("Пиши... пиши...");
    vecTextTry.push_back("А може, літери не варто писати?");
    vecTextTry.push_back("І хто взагалі це придумав?");
    vecTextTry.push_back("Опа, опа... Гаразд, жартую");
    vecTextTry.push_back("200520 — далі вже здогадайся сам");
    vecTextTry.push_back("Пароль не складний");
    vecTextTry.push_back("А може, літери не варто писати?");
    vecTextTry.push_back("Пароль не складний");
    vecTextTry.push_back("Опа, опа... Гаразд, жартую");
    vecTextTry.push_back("Опа, опа... Гаразд, жартую");

}
