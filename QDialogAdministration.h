#ifndef QDIALOGADMINISTRATION_H
#define QDIALOGADMINISTRATION_H

#include "QDialog"
#include "QString"
#include "QtWidgets"


class QDialogAdministration : public QDialog
{
    Q_OBJECT
public:
    QDialogAdministration(QWidget *parent = 0);

    QGridLayout *gridLayout;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    QVector <QString> vecTextTry;

    void setupBody();
    void fillVectorTry();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

};

#endif // QDIALOGADMINISTRATION_H
