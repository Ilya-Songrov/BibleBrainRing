#pragma once

#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>

class InformationConsolePrinter
{
public:
    static void printArrAndMessage(const QJsonDocument &doc, const QString &debugMessage, const bool useWarning = false);
    static void printArrAndMessage(const QByteArray &arr, const QString &debugMessage, const bool useWarning = false);
    static void printArrAndMessage(const QJsonDocument &doc, const QString &debugMessage, const QString &color, const bool useWarning = false);
    static void printArrAndMessage(const QByteArray &arr, const QString &debugMessage, const QString &color, const bool useWarning = false);
};

