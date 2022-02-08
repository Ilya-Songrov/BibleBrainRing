#include "stateabstract.h"


StateAbstract::StateAbstract(const QString &objectName, QObject *parent) : QObject(parent)
{
    setObjectName(objectName);
    printCurrentState();

}

StateAbstract *StateAbstract::onEndQmlCreation()
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

StateAbstract *StateAbstract::onQmlButtonClicked(const BibleBrainRing::Button button)
{
    qWarning() << "Not processed:" << "State: " + objectName() << "function: " + QString(Q_FUNC_INFO)
               << "button:" << button
               << QDateTime::currentDateTime().toString("yyyy:MM:dd - hh:mm:ss:zzz") << Qt::endl;
    return nullptr;
}

void StateAbstract::printCurrentState()
{
    qDebug() << "\033[1mCurrent state:" << objectName() << QDateTime::currentDateTime().toString("dd:MM:yyyy - hh:mm:ss:zzz") << "\033[0m" << Qt::endl;
}


