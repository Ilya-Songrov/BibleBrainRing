#include "information/informationconsoleprinter.h"


void InformationConsolePrinter::printArrAndMessage(const QJsonDocument &doc, const QString &debugMessage, const bool useWarning)
{
    printArrAndMessage(doc.toJson(), debugMessage, useWarning);
}

void InformationConsolePrinter::printArrAndMessage(const QByteArray &arr, const QString &debugMessage, const bool useWarning)
{
    const QJsonDocument doc = QJsonDocument::fromJson(arr);
    if (useWarning) {
        qWarning() << debugMessage
                   << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl
                   << qPrintable(doc.isEmpty() ? arr : doc.toJson())
                   << Qt::endl;
        return;
    }
    qDebug() << debugMessage
             << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl
             << qPrintable(doc.isEmpty() ? arr : doc.toJson())
             << Qt::endl;
}

void InformationConsolePrinter::printArrAndMessage(const QJsonDocument &doc, const QString &debugMessage, const QString &color, const bool useWarning)
{
    printArrAndMessage(doc.toJson(), debugMessage, color, useWarning);
}

void InformationConsolePrinter::printArrAndMessage(const QByteArray &arr, const QString &debugMessage, const QString &color, const bool useWarning)
{
    if (useWarning || color.isEmpty()) {
        InformationConsolePrinter::printArrAndMessage(arr, debugMessage, useWarning);
        return;
    }
    QString colorWithsSemicol = color;
    colorWithsSemicol.replace(",", ";");
    qDebug() << QByteArray("\033[38;2;" + colorWithsSemicol.toUtf8() + "m").constData();
    InformationConsolePrinter::printArrAndMessage(arr, debugMessage, useWarning);
    qDebug() << "\033[0m";
}
