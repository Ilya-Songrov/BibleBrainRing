#include "InformationSettings.h"

QRect InformationSettings::rectPrimaryScreen;

InformationSettings::InformationSettings() : InformationAbstract()
{

}

void InformationSettings::initValues()
{
    initRectPrimaryScreen();
}

const QRect &InformationSettings::getRectPrimaryScreen()
{
    return rectPrimaryScreen;
}

void InformationSettings::initRectPrimaryScreen()
{
#ifdef QT_DEBUG
    const QRect rect { QGuiApplication::screens().constLast()->geometry() };
    rectPrimaryScreen = QRect(QPoint(), QSize(4, 3) * 220);
    rectPrimaryScreen.moveCenter(rect.center());
#else
    rectPrimaryScreen = QGuiApplication::primaryScreen()->geometry();
#endif
}


