#pragma once

#include <QObject>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QUrl>
#include <QFileInfo>
#include <QMessageBox>
#include <QVector>

class ManagerQuestions : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QStringList searchingQuestions READ getSearchingQuestions WRITE setSearchingQuestions NOTIFY searchingQuestionsChanged)
public:
    explicit ManagerQuestions(QObject *parent = nullptr);

    void setSearchingQuestions(const QStringList& questions);
    QStringList getSearchingQuestions();

    Q_INVOKABLE QString loadQuestions(const QString fileUrls);
    Q_INVOKABLE QStringList updateSearchQuestions(const QString& subStr);

signals:
    void searchingQuestionsChanged();

private:
    QVector<QString> allQuestions;
    QStringList searchingQuestions;
};

