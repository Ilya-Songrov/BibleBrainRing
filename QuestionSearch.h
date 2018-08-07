#ifndef QUESTIONSEARCH_H
#define QUESTIONSEARCH_H

#include "ui_mainwindow.h"
#include "myProxyStyleHTMLdelegate.h"
#include "QuestionPreviewForm.h"

#include "QObject"
#include "QVector"
#include "QList"
#include "QtWidgets"
#include "QMap"
#include "QTextCodec"
#include "QString"
#include "QMessageBox"

QT_BEGIN_NAMESPACE
class QuestionPreviewForm;
QT_END_NAMESPACE


class QuestionSearch : public QObject
{
    Q_OBJECT
public:
    QuestionSearch(Ui::MainWindow *uiMain, QWidget *parent = Q_NULLPTR);
    ~QuestionSearch();

    Ui::MainWindow *ui;
    QWidget *parentMain;
    QuestionPreviewForm *questionPreviewForm;
    QVector <QString> vecText_questions;

private slots:
    void slotTextChanged(const QString &);
    void slotOnPushButton_Search_clicked();
public slots:
    void questionFastLoad(bool boolQuestionsonEsther = false);
    void showPreviewFormDecoder(QString currentPath);
    QStringList search(QString strRequest);

signals:
    void signalShowQuestion(QString str);
};

#endif // QUESTIONSEARCH_H
