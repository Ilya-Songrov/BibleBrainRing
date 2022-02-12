#pragma once

#include <QObject>

class QuestionsFileParser : public QObject
{
    Q_OBJECT
public:
    explicit QuestionsFileParser(QObject *parent = nullptr);

};

