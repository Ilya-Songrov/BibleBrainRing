#ifndef QUESTIONSEARCH_H
#define QUESTIONSEARCH_H

#include "ui_mainwindow.h"
#include "MyProxyStyleHTMLdelegate.h"
#include "QuestionPreviewForm.h"

#include "QObject"
#include "QVector"
#include "QList"
#include "QtWidgets"
#include "QMap"
#include "QTextCodec"
#include "QString"
#include "QMessageBox"
#include "QFileInfo"
#include "QTimer"

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
    QString lastUsedQuestionFilePath; // зберігаємо останній використаний шлях до файла з питаннями

private slots:
    void slotTextChanged(const QString &);
    void slotOnPushButton_Search_clicked();
public slots:
    void questionFastLoad(bool boolQuestionsonEsther = false);
    void showPreviewFormDecoder(QString currentPath);
    QStringList search(QString strRequest);
    void setLastUsedQuestionFilePath(const QString &filePath) { lastUsedQuestionFilePath = filePath; } // встановлення шляху
    QString getLastUsedQuestionFilePath() const { return lastUsedQuestionFilePath; } // отримання шляху
    void autoLoadQuestions(); // автоматичне завантаження питань з збереженого файла
    bool hasQuestions() const { return vecText_questions.size() > 0; } // перевірка наявності питань

signals:
    void signalShowQuestion(QString str);
    void questionsLoaded(bool hasQuestions); // сигнал про стан завантаження питань
};

#endif // QUESTIONSEARCH_H
