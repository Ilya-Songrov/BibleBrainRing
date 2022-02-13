#include "ManagerQuestions.hpp"

ManagerQuestions::ManagerQuestions(QObject *parent)
    : QObject{parent}
{

}

void ManagerQuestions::setSearchingQuestions(const QStringList& questions)
{
    searchingQuestions = questions;
    emit searchingQuestionsChanged();
}

QStringList ManagerQuestions::getSearchingQuestions()
{
    return searchingQuestions;
}

QString ManagerQuestions::loadQuestions(const QString fileUrls)
{
    allQuestions.clear();
    QFile inputFile(QUrl(fileUrls).toLocalFile());
    if (!inputFile.open(QIODevice::ReadOnly)){
        QMessageBox::warning(nullptr, QObject::tr("Codecs"), QString("Cannot read file %1").arg(QUrl(fileUrls).toLocalFile()));
    }
    QTextStream in(&inputFile);
    while (!in.atEnd())
    {
        QString line = in.readLine();
        if(!line.isEmpty()){
            allQuestions.push_back(line);
            searchingQuestions.push_back(line);
        }
    }
    inputFile.close();
    if (allQuestions.isEmpty()) {
        QMessageBox::warning(nullptr, QObject::tr("Codecs"), "Qestions was not loaded");
    }
    updateSearchQuestions("");
    return searchingQuestions.join("\n");
}

QStringList ManagerQuestions::updateSearchQuestions(const QString& subStr)
{
    searchingQuestions.clear();
    for (const QString& q : qAsConst(allQuestions)) {
        const auto qToUpper = q.toUpper();
        if (qToUpper.contains(subStr.toUpper())) {
            searchingQuestions.append(q);
        }
    }
    emit searchingQuestionsChanged();
    return searchingQuestions;
}


